#include "Tu_filedevice.h"
#include <QDebug>

FileDevice::FileDevice()
{

}

FileDevice::~FileDevice()
{

}

bool FileDevice::deleteFile(const QString &path)
{
	QFile file(path);

	if (!file.exists()) {
		qWarning() << "File does not exist!";
		return false;
	}

	if (!file.remove()) {
		qWarning() << "File deletion failed!";
		return false;
	}

	return true;
}

bool FileDevice::deleteDir(const QString &path)
{
	QDir dir(path);

	if (!dir.exists()) {
		qWarning() << "Dir does not exist!";
		return false;
	}

	if (!dir.rmdir(path)) {
		qWarning() << "Dir deletion failed!";
		return false;
	}

	return true;
}

bool FileDevice::createFile(const QString &path)
{
	QFile file(path);

	if (file.exists()) {
		return true;
	}

	bool isOpen = file.open(QIODevice::WriteOnly);
	file.close();

	if (!isOpen) {
		qWarning() << "File create failed!";
	}

	return isOpen;
}

bool FileDevice::createDir(const QString &path)
{
	QDir dir(path);

	if (!dir.mkpath(path)) {
		qWarning() << "Directory creation failed!";
		return false;
	}

	return true;
}

bool FileDevice::renameFile(const QString &oldName, const QString &newName)
{
	QDir dir(oldName);

	if (!dir.exists()) {
		qWarning() << "File does not exist!";
		return false;
	}

	if (dir.rename(oldName, newName)) {
		qWarning() << "File rename failed!";
		return false;
	}

	return true;
}

bool FileDevice::copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist)
{
	toDir.replace("\\", "/");

	if (sourceDir == toDir){
		return true;
	}

	if (!QFile::exists(sourceDir)){
		return false;
	}

	QDir dir(toDir);
	if (dir.exists() && coverFileIfExist){
		dir.remove(toDir);
	}

	if (!QFile::copy(sourceDir, toDir)){
		return false;
	}

	return true;
}

bool FileDevice::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
	QDir sourceDir(fromDir);
	QDir targetDir(toDir);

	if (!targetDir.exists()){  
		if (!targetDir.mkdir(targetDir.absolutePath()))
			return false;
	}

	QFileInfoList fileInfoList = sourceDir.entryInfoList();
	foreach(QFileInfo fileInfo, fileInfoList){
		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
			continue;

		if (fileInfo.isDir()){   
			if (!copyDirectoryFiles(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName()), coverFileIfExist))
				return false;
		} else {           
			if (coverFileIfExist && targetDir.exists(fileInfo.fileName())) {
				targetDir.remove(fileInfo.fileName());
			}

			if (!QFile::copy(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName()))) {
				return false;
			}
		}
	}

	return true;
}

bool FileDevice::isFileExist(const QString &filename)
{
	QFileInfo fileInfo(filename);

	if (!fileInfo.isFile()) {
		return false;
	}

	return true;
}

bool FileDevice::isDirExist(const QString &dirname)
{
	QFileInfo fileInfo(dirname);

	if (!fileInfo.isDir()) {
		return false;
	}

	return true;
}
