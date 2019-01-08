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
	quint64	totalWritten = 0;          // 已经写入的总字节数
	qlonglong bytesWritten = 0;        // 每次写入的数据量
	DWORD   bytesToWrite = 0;          // 实践写入的数据量
	BOOLEAN		status = false;
	qlonglong seekLength = (qlonglong)length;

	for (int i = 0; i < 3; ++i) {
		if (i != 0) {
			// 设置到初始写位置
			SetFilePointer(FileHandle, -seekLength, NULL, FILE_CURRENT);
		}

		totalWritten = 0;   // 已经写入的总字节数
		while (totalWritten < seekLength)
		{
			if (length - totalWritten > 1024 * 1024) {
				bytesToWrite = 1024 * 1024;               // 每次写入的数据量
			} else {
				bytesWritten = seekLength - totalWritten; // 计算剩余可以写入字节数
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

	// FILE_FLAG_WRITE_THROUGH  指示系统立即写磁盘。这个写操作允许被cache缓存，但不能被搁置。
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

	// 重命名26次
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
	BOOLEAN	   reallyCompressed = false;   // 是否确定为压缩文件
	BOOLEAN	   zappedFile = false;         // 是否能写垃圾数据到文件的磁盘空间
	TCHAR	   lastFileName[MAX_PATH];

	static QString	volumeName = "\\\\.\\A:";   // 文件所在的磁盘卷名 格式  \\.\X  (X为盘符)
	static QString	volumeRoot = "A:\\";        // 文件所在的磁盘
	static HANDLE	hVolume = INVALID_HANDLE_VALUE;
	static DWORD	clusterSize;                // 一个簇的字节数

	DWORD	sectorsPerCluster;      // 用于装载一个簇内扇区数
	DWORD   bytesPerSector;         // 用于装载一个扇区内字节数
	DWORD   freeClusters;           // 用于装载磁盘上剩余簇数
	DWORD   totalClusters;          // 用于装载磁盘上总簇数

	/*
	lpRootPathName String，不包括卷名的一个磁盘根路径
	lpSectorsPerCluster Long，用于装载一个簇内扇区数的变量
	lpBytesPerSector Long，用于装载一个扇区内字节数的变量
	lpNumberOfFreeClusters Long，用于装载磁盘上剩余簇数的变量
	lpTtoalNumberOfClusters Long，用于装载磁盘上总簇数的变量
	*/
	if (INVALID_HANDLE_VALUE == hVolume) {
		volumeName[4] = FileName[0];
		// 打开磁盘卷
		hVolume = CreateFile(volumeName.toStdWString().c_str(), GENERIC_READ | GENERIC_WRITE,
							 FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,  0, 0);

		volumeRoot[0] = FileName[0];
		// 获得逻辑磁盘情况
		GetDiskFreeSpace(volumeRoot.toStdWString().c_str(), &sectorsPerCluster, &bytesPerSector,
						 &freeClusters, &totalClusters);

		clusterSize = bytesPerSector * sectorsPerCluster; // 一个簇的字节数
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

	// PGET_RETRIEVAL_DESCRIPTOR结构描述文件在磁盘上 簇个数， 逻辑簇和虚拟簇编号信息
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
		// 判断是否为NT压缩文件
		// NT压缩文件第一个逻辑簇编号不等于为-1
		if (fileMappings->Pair[i].Lcn != LINVALID) {
			*realcompress = true;

			if (VolumeHandle != INVALID_HANDLE_VALUE) {
				clusterOffset = fileMappings->Pair[i].Lcn * clusterSize;    // 计算簇在磁盘上的位置
				SetFilePointer(VolumeHandle, clusterOffset, 0, FILE_BEGIN); // 定位到这个簇这个位置

				// 对该簇写垃圾数据
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

		// 粉碎文件
		// 判断文件类型
		DWORD FileAttr = GetFileAttributes(absolutefile.toStdWString().c_str());
		if (FileAttr == INVALID_FILE_ATTRIBUTES) {
			return false;
		}

		if (FileAttr & FILE_ATTRIBUTE_COMPRESSED || FileAttr & FILE_ATTRIBUTE_SPARSE_FILE || FileAttr & FILE_ATTRIBUTE_ENCRYPTED) {
			safeDeleteCompressed(absolutefile);
		} else {
			// 先删除
			safeDelete(absolutefile, qfile.size());
		}

		qfile.close();
		QString LastName;

		// 重命名26次
		safeRename(absolutefile, LastName);

		//删除文件
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
	//	MsgBoxDlg msgdog(tr("文件粉碎"), tr("无法清除UNC类型驱动设备!"));
		return;
	}

	if (!GetDiskFreeSpace(DrivePath.toStdWString().c_str(), &sectorsPerCluster, &bytesPerSector, &freeClusters, &totalClusters)) {
		return;
	}

	bytesAvail = sectorsPerCluster * freeClusters * bytesPerSector; // 剩余空间字节数
	freeBytes = bytesAvail; // 当前可用空间

	if (freeBytes != bytesAvail) {
// 		MsgBoxDlg msgdog(tr("文件粉碎"), tr("用户被限定磁盘配额，无法执行操作!"));
// 		msgdog.exec();
		return;
	}

	QString tempFileNameOne = DrivePath + "qjpdel_temp";
	hTempFileOne = CreateFile(tempFileNameOne.toStdWString().c_str(), GENERIC_WRITE,  0, NULL, CREATE_ALWAYS,
							  FILE_FLAG_NO_BUFFERING | FILE_FLAG_SEQUENTIAL_SCAN | FILE_FLAG_DELETE_ON_CLOSE | FILE_ATTRIBUTE_HIDDEN, NULL);

	if (INVALID_HANDLE_VALUE == hTempFileOne) {
		QString Error = PrintWin32Error(GetLastError());
// 		MsgBoxDlg msgdog(tr("文件粉碎"), Error);
// 		msgdog.exec();
		return;
	}

	quint64 tempSize = 0;
	// 分配128个簇字节大小空间,每次清理的空间大小
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

	// 清除小于一个簇空间大小
	QString tempFileNameSecond = DrivePath + "qjpdel_temp_second";
	hTenpFileSecond = CreateFile(tempFileNameSecond.toStdWString().c_str(), GENERIC_WRITE, 0, NULL, CREATE_NEW,
								 FILE_FLAG_SEQUENTIAL_SCAN | FILE_FLAG_DELETE_ON_CLOSE |  FILE_ATTRIBUTE_HIDDEN | FILE_FLAG_WRITE_THROUGH, NULL);

	if (INVALID_HANDLE_VALUE == hTenpFileSecond) {
		QString Error = PrintWin32Error(GetLastError());
// 		MsgBoxDlg msgdog(tr("文件粉碎"), Error);
// 		msgdog.exec();
		return;
	}

	while (cleanSize) {
		if (!safeWrite(hTempFileOne, cleanSize)) {
			--cleanSize;
		}
	}

	// 写ntfs的MTF表
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
		createdFile = FALSE; // 是否创建文件标志，如果为false表示没有磁盘空间可以分配

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
