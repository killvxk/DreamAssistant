#include "Tu_filewipe.h"
#include <time.h>
#include <assert.h>

#define  CLEANBUFSIZE    (65536)
#define	 FILEMAPSIZE	 (16384+2)
#define  LINVALID        (-1)

FileWipe::FileWipe(QObject *parent)
	: QObject(parent)
{

}

FileWipe::~FileWipe()
{

}

FileWipe *FileWipe::Instance()
{
	static FileWipe fileWipe;
	return &fileWipe;
}

void FileWipe::memmoryAlloc()
{
	qsrand((unsigned)time(NULL));

	for (int i = 0; i < 3; ++i) {
		m_cleanBuffer[i] = (PBYTE)VirtualAlloc(NULL, CLEANBUFSIZE, MEM_COMMIT, PAGE_READWRITE);
		if (!m_cleanBuffer[i]) {
			for (int j = 0; j < i; j++) {
				VirtualFree(m_cleanBuffer[j], 0, MEM_RELEASE);
			}
			return;
		}

		switch (i) {
		case 0:
			break;
		case 1:
			memset(m_cleanBuffer[i], 0xFF, CLEANBUFSIZE);
			break;
		case 2:
			for (int j = 0; j < CLEANBUFSIZE; j++) {
				m_cleanBuffer[i][j] = (BYTE)qrand();
			}
			break;
		}
	}
}

bool FileWipe::safeWrite(HANDLE FileHandle, qint64 length)
{
	quint64	totalWritten = 0;          // �Ѿ�д������ֽ���
	qlonglong bytesWritten = 0;        // ÿ��д���������
	DWORD   bytesToWrite = 0;          // ʵ��д���������
	BOOLEAN		status = false;
	qlonglong seekLength = (qlonglong)length;

	for (int i = 0; i < 3; ++i) {
		if (i != 0) {
			// ���õ���ʼдλ��
			SetFilePointer(FileHandle, -seekLength, NULL, FILE_CURRENT);
		}

		totalWritten = 0;   // �Ѿ�д������ֽ���
		while (totalWritten < seekLength)
		{
			if (length - totalWritten > 1024 * 1024) {
				bytesToWrite = 1024 * 1024;               // ÿ��д���������
			} else {
				bytesWritten = seekLength - totalWritten; // ����ʣ�����д���ֽ���
			}
			if (bytesToWrite > CLEANBUFSIZE)
				bytesToWrite = CLEANBUFSIZE;

			status = WriteFile(FileHandle, m_cleanBuffer[i], bytesWritten, &bytesToWrite, NULL);
			if (!status)
				return false;
			totalWritten += bytesToWrite;
		}
	}
	return true;
}

bool FileWipe::safeDelete(QString FileName, quint64 length)
{
	HANDLE	hFile = NULL;
	qlonglong bytesToWrite;
	qlonglong bytesWritten;
	long DisMoveHeigth = 0;
	quint64 fileLength;
	TCHAR   lastFileName[MAX_PATH];

	// FILE_FLAG_WRITE_THROUGH  ָʾϵͳ����д���̡����д��������cache���棬�����ܱ����á�
	hFile = CreateFile(FileName.toStdWString().c_str(), GENERIC_WRITE,
					   FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH, NULL);

	if (hFile == INVALID_HANDLE_VALUE) {
		return false;
	}

	if (length > 0) {
		SetFilePointer(hFile, length - 1, &DisMoveHeigth, FILE_END);

		if (!safeWrite(hFile, 1)) {
			CloseHandle(hFile);
			return false;
		}

		SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
		bytesToWrite = 0;

		while (bytesToWrite < length)
		{
			bytesWritten = qMin((quint64)length - bytesToWrite, (quint64)CLEANBUFSIZE);
			if (!safeWrite(hFile, bytesWritten)) {
				CloseHandle(hFile);
				return false;
			}
			bytesToWrite += bytesWritten;
		}

		CloseHandle(hFile);
		return true;
	}

	return false;
}

bool FileWipe::safeRename(QString FileName, QString& Lastname)
{
	FileName = QDir::fromNativeSeparators(FileName);

	QString NewFilename = FileName;
	QString name = FileName;

	int index = FileName.lastIndexOf('/');
	int len = FileName.length() - index;

	// ������26��
	char och = 'A';
	for (int i = 0; i < 26; ++i)
	{
		char ch = och + (uchar)i;
		for (int j = 1; j < len; ++j) {
			if (FileName[index + j] == '.') {
				continue;
			}
			NewFilename[index + j] = ch;
		}

		QString temp_name = QDir::toNativeSeparators(name);
		QString temp_NewFile = QDir::toNativeSeparators(NewFilename);

		if (!QFile::rename(temp_name, temp_NewFile)) {
			return false;
		}
		name = NewFilename;
	}

	Lastname = name;
	return true;
}

bool FileWipe::safeDeleteCompressed(QString FileName)
{
	HANDLE	   hFile;
	BOOLEAN	   reallyCompressed = false;   // �Ƿ�ȷ��Ϊѹ���ļ�
	BOOLEAN	   zappedFile = false;         // �Ƿ���д�������ݵ��ļ��Ĵ��̿ռ�
	TCHAR	   lastFileName[MAX_PATH];

	static QString	volumeName = "\\\\.\\A:";   // �ļ����ڵĴ��̾��� ��ʽ  \\.\X  (XΪ�̷�)
	static QString	volumeRoot = "A:\\";        // �ļ����ڵĴ���
	static HANDLE	hVolume = INVALID_HANDLE_VALUE;
	static DWORD	clusterSize;                // һ���ص��ֽ���

	DWORD	sectorsPerCluster;      // ����װ��һ������������
	DWORD   bytesPerSector;         // ����װ��һ���������ֽ���
	DWORD   freeClusters;           // ����װ�ش�����ʣ�����
	DWORD   totalClusters;          // ����װ�ش������ܴ���

	/*
	lpRootPathName String��������������һ�����̸�·��
	lpSectorsPerCluster Long������װ��һ�������������ı���
	lpBytesPerSector Long������װ��һ���������ֽ����ı���
	lpNumberOfFreeClusters Long������װ�ش�����ʣ������ı���
	lpTtoalNumberOfClusters Long������װ�ش������ܴ����ı���
	*/
	if (INVALID_HANDLE_VALUE == hVolume) {
		volumeName[4] = FileName[0];
		// �򿪴��̾�
		hVolume = CreateFile(volumeName.toStdWString().c_str(), GENERIC_READ | GENERIC_WRITE,
							 FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,  0, 0);

		volumeRoot[0] = FileName[0];
		// ����߼��������
		GetDiskFreeSpace(volumeRoot.toStdWString().c_str(), &sectorsPerCluster, &bytesPerSector,
						 &freeClusters, &totalClusters);

		clusterSize = bytesPerSector * sectorsPerCluster; // һ���ص��ֽ���
	}

	hFile = CreateFile(FileName.toStdWString().c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		return true;
	}

	return safeWriteCompressedFile(hVolume, hFile, clusterSize, &m_realcompress, &m_zap);
}

bool FileWipe::safeWriteCompressedFile(HANDLE VolumeHandle, HANDLE hFile,  DWORD clusterSize, bool* realcompress,  bool* zap)
{
	DWORD						      status;
	IO_STATUS_BLOCK				      ioStatus;
	ULONGLONG					      startVcn, prevVcn;
	quint64				              clusterOffset;
	quint64					          endOfPrevRun;
	PGET_RETRIEVAL_DESCRIPTOR	      fileMappings;
	quint64					          fileMap[FILEMAPSIZE];
	int						          lines = 0;

	*realcompress = false;
	*zap = false;

	startVcn = 0;
	endOfPrevRun = -1;

	// PGET_RETRIEVAL_DESCRIPTOR�ṹ�����ļ��ڴ����� �ظ����� �߼��غ�����ر����Ϣ
	fileMappings = (PGET_RETRIEVAL_DESCRIPTOR)fileMap;

	while (!(status = m_NtFsControlFile(hFile, NULL, NULL, 0, &ioStatus, FSCTL_GET_RETRIEVAL_POINTERS,
		&startVcn, sizeof(startVcn), fileMappings, FILEMAPSIZE * sizeof(ULONGLONG))) ||
		status == STATUS_BUFFER_OVERFLOW || status == STATUS_PENDING)
	{
		if (status == STATUS_PENDING) {
			WaitForSingleObject(hFile, INFINITE);

			if (ioStatus.Status != STATUS_SUCCESS && ioStatus.Status != STATUS_BUFFER_OVERFLOW) {
				return ioStatus.Status == STATUS_SUCCESS;
			}
		}
	}

	startVcn = fileMappings->StartVcn;
	prevVcn = fileMappings->StartVcn;

	for (quint64 i = 0; i < (quint64)fileMappings->NumberOfPairs; i++) {
		// �ж��Ƿ�ΪNTѹ���ļ�
		// NTѹ���ļ���һ���߼��ر�Ų�����Ϊ-1
		if (fileMappings->Pair[i].Lcn != LINVALID) {
			*realcompress = true;

			if (VolumeHandle != INVALID_HANDLE_VALUE) {
				clusterOffset = fileMappings->Pair[i].Lcn * clusterSize;    // ������ڴ����ϵ�λ��
				SetFilePointer(VolumeHandle, clusterOffset, 0, FILE_BEGIN); // ��λ����������λ��

				// �Ըô�д��������
				if (!safeWrite(hFile, clusterSize * (DWORD)(fileMappings->Pair[i].Vcn - startVcn))) {
					CloseHandle(hFile);
					return true;
				}
			}
		}
	}

	return true;
}

void FileWipe::getFiels(QString odir, QStringList& absolutePaths)
{
	QDir dir(odir);
	QStringList dires = dir.entryList(QDir::Dirs | QDir::Files, QDir::Name);

	if (!(dires.isEmpty())) {
		QStringList::Iterator dit = dires.begin();

		while (dit != dires.end()) {
			if ((*dit == ".") || (*dit == ".."));
			else
			{
				QString m = odir + "/" + *dit;
				QFileInfo info(m);

				if (info.isFile()) {
					absolutePaths.append(m);
				} else {
					getFiels(m, absolutePaths);
				}
			}
			++dit;
		}
	}
}

bool FileWipe::getNativeEntryPoints()
{
	if (GetVersion() >= 0x80000000)
		return false;

	if (!(m_NtFsControlFile = (PNtFsControlFile)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtFsControlFile"))) {
		return false;
	}

	if (!(m_RtlNtStatusToDosError = (PRtlNtStatusToDosError)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "RtlNtStatusToDosError"))) {
		return false;
	}

	return true;
}

bool FileWipe::startWipeFile(QStringList EraseList)
{
	int count = EraseList.count();
	QStringList absolutePaths;

	for (int i = 0; i < count; ++i) 
	{
		QString item = EraseList.at(i);
		QFileInfo qinfo(item);

		if (qinfo.isDir()) {
			QDir dir(item);
			getFiels(dir.absolutePath(), absolutePaths);
		} else {
			absolutePaths.append(item);
		}
	}

	int erase_count = absolutePaths.count();
	for (int i = 0; i < erase_count; ++i)
	{
		QString absolutefile = absolutePaths.at(i);
		QFile qfile(absolutefile);

		if (!qfile.exists(absolutefile)) {
			continue;
		}

		// �����ļ�
		// �ж��ļ�����
		DWORD FileAttr = GetFileAttributes(absolutefile.toStdWString().c_str());
		if (FileAttr == INVALID_FILE_ATTRIBUTES) {
			return false;
		}

		if (FileAttr & FILE_ATTRIBUTE_COMPRESSED || FileAttr & FILE_ATTRIBUTE_SPARSE_FILE || FileAttr & FILE_ATTRIBUTE_ENCRYPTED) {
			safeDeleteCompressed(absolutefile);
		} else {
			// ��ɾ��
			safeDelete(absolutefile, qfile.size());
		}

		qfile.close();
		QString LastName;

		// ������26��
		safeRename(absolutefile, LastName);

		//ɾ���ļ�
		if (!QFile::remove(LastName)) {
			QFile::rename(LastName, absolutefile);
		}
	}
	return true;
}

void FileWipe::cleanFreeSpace()
{
	QString  DrivePath = "D:\\";
	quint64  bytesAvail, totalBytes, freeBytes;
	DWORD	 sectorsPerCluster, bytesPerSector, totalClusters, freeClusters;
	quint64	 prevSize, cleanSize;
	HANDLE	 hTempFileOne = INVALID_HANDLE_VALUE;
	HANDLE   hTenpFileSecond = INVALID_HANDLE_VALUE;
	BOOLEAN	 createdFile;
	DWORD	 percent, mftFilesCreated;
	DWORD	 prevPercent = 0;

	if (DrivePath[1] != ':') {
	//	MsgBoxDlg msgdog(tr("�ļ�����"), tr("�޷����UNC���������豸!"));
		return;
	}

	if (!GetDiskFreeSpace(DrivePath.toStdWString().c_str(), &sectorsPerCluster, &bytesPerSector, &freeClusters, &totalClusters)) {
		return;
	}

	bytesAvail = sectorsPerCluster * freeClusters * bytesPerSector; // ʣ��ռ��ֽ���
	freeBytes = bytesAvail; // ��ǰ���ÿռ�

	if (freeBytes != bytesAvail) {
// 		MsgBoxDlg msgdog(tr("�ļ�����"), tr("�û����޶��������޷�ִ�в���!"));
// 		msgdog.exec();
		return;
	}

	QString tempFileNameOne = DrivePath + "qjpdel_temp";
	hTempFileOne = CreateFile(tempFileNameOne.toStdWString().c_str(), GENERIC_WRITE,  0, NULL, CREATE_ALWAYS,
							  FILE_FLAG_NO_BUFFERING | FILE_FLAG_SEQUENTIAL_SCAN | FILE_FLAG_DELETE_ON_CLOSE | FILE_ATTRIBUTE_HIDDEN, NULL);

	if (INVALID_HANDLE_VALUE == hTempFileOne) {
		QString Error = PrintWin32Error(GetLastError());
// 		MsgBoxDlg msgdog(tr("�ļ�����"), Error);
// 		msgdog.exec();
		return;
	}

	quint64 tempSize = 0;
	// ����128�����ֽڴ�С�ռ�,ÿ������Ŀռ��С
	cleanSize = (quint64)sectorsPerCluster * (quint64)bytesPerSector * 128;

	while (cleanSize > sectorsPerCluster * bytesPerSector)
	{
		if (safeWrite(hTempFileOne, cleanSize)) {
			tempSize += cleanSize;
			percent = (DWORD)((tempSize * 100) / freeBytes);

			emit sig_updateProgressValue(percent);
		} else {
			cleanSize -= sectorsPerCluster * bytesPerSector;
		}
	}

	// ���С��һ���ؿռ��С
	QString tempFileNameSecond = DrivePath + "qjpdel_temp_second";
	hTenpFileSecond = CreateFile(tempFileNameSecond.toStdWString().c_str(), GENERIC_WRITE, 0, NULL, CREATE_NEW,
								 FILE_FLAG_SEQUENTIAL_SCAN | FILE_FLAG_DELETE_ON_CLOSE |  FILE_ATTRIBUTE_HIDDEN | FILE_FLAG_WRITE_THROUGH, NULL);

	if (INVALID_HANDLE_VALUE == hTenpFileSecond) {
		QString Error = PrintWin32Error(GetLastError());
// 		MsgBoxDlg msgdog(tr("�ļ�����"), Error);
// 		msgdog.exec();
		return;
	}

	while (cleanSize) {
		if (!safeWrite(hTempFileOne, cleanSize)) {
			--cleanSize;
		}
	}

	// дntfs��MTF��
	mftFilesCreated = 0;
	// max MFT record size
	prevSize = 4096;
	QString tempFileNameMFT;

	while (true)
	{
		QString CreatedCount;
		CreatedCount.setNum(mftFilesCreated);
		tempFileNameMFT = DrivePath + "SDELMFT" + CreatedCount;
		HANDLE hTempFile = CreateFile(tempFileNameMFT.toStdWString().c_str(), GENERIC_WRITE, 0, NULL, CREATE_NEW,
									  FILE_FLAG_SEQUENTIAL_SCAN | FILE_FLAG_DELETE_ON_CLOSE | FILE_ATTRIBUTE_HIDDEN, NULL);

		if (hTempFile == INVALID_HANDLE_VALUE) {
			break;
		}

		cleanSize = prevSize;
		createdFile = FALSE; // �Ƿ񴴽��ļ���־�����Ϊfalse��ʾû�д��̿ռ���Է���

		while (cleanSize) {
			if (!safeWrite(hTempFile, cleanSize)) {
				cleanSize--;
			} else {
				prevSize = cleanSize;
				createdFile = true;
			}
		}

		if (!createdFile)
			break;
	}
}

QString FileWipe::PrintWin32Error(DWORD ErrorCode)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				  NULL, ErrorCode,
				  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				  (LPTSTR)&lpMsgBuf, 0, NULL);

	QString qerror = QString::fromStdWString((LPTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);

	return qerror;
}
