#ifndef TU_FILEWIPE_H
#define TU_FILEWIPE_H

#include <QDir>

#include "Tu_define.h"

class FileWipe : public QObject
{
	Q_OBJECT
public:
	explicit FileWipe(QObject *parent = Q_NULLPTR);
	~FileWipe();

	static FileWipe *Instance();

	bool startWipeFile(QStringList EraseList);
	void cleanFreeSpace();

signals:
	void sig_updateProgressValue(int value);

protected:
	void memmoryAlloc();

	bool safeWrite(HANDLE FileHandle, qint64 length);
	bool safeDelete(QString FileName, quint64 length);
	bool safeRename(QString FileName, QString& Lastname);
	bool safeDeleteCompressed(QString FileName);
	bool safeWriteCompressedFile(HANDLE VolumeHandle, HANDLE hFile, DWORD clusterSize, bool* realcompress, bool* zap);

	void getFiels(QString odir, QStringList& absolutePaths);
	bool getNativeEntryPoints();

	QString PrintWin32Error(DWORD ErrorCode);

private:
	QStringList  m_EraseList;         //删除列表保存要删除的文件和路径
	PBYTE	     m_cleanBuffer[3];

	PNtFsControlFile  m_NtFsControlFile;
	PRtlNtStatusToDosError m_RtlNtStatusToDosError;
	PGetDiskFreeSpaceEx    m_PGetDiskFreeSpaceEx;

	bool m_realcompress;
	bool m_zap;
};

#endif // TU_FILEWIPE_H
