#ifndef TU_FILEDEVICE_H
#define TU_FILEDEVICE_H

#include <QDir>
#include <QFile>
#include <QFileInfo>

#include "../Tu-core/Tu_singleton.h"

class FileDevice
{
	SINGLETON(FileDevice)
public:
	bool deleteFile(const QString &path);
	bool deleteDir(const QString &path);

	bool createFile(const QString &path);
	bool createDir(const QString &path);

	bool renameFile(const QString &oldName, const QString &newName);

	bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
	bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);

	bool isFileExist(const QString &filename);
	bool isDirExist(const QString &dirname);
};

#endif // TU_FILEDEVICE_H
