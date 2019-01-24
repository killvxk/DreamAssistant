#include "Tu_systemdispatcher.h"
#include "../Tu-device/Tu_filedevice.h"
#include <QCoreApplication>

SystemDispatcher::SystemDispatcher(QObject *parent)
	: QObject(parent)
{
	
}

SystemDispatcher::~SystemDispatcher()
{

}

bool SystemDispatcher::copy_file(QString filename)
{
    QString target_path = QCoreApplication::applicationDirPath().append("skin/custom/");

	return FileDevice::copyFile(filename.toLatin1().data(), target_path.toLatin1().data());
}

bool SystemDispatcher::delete_file(QString filename)
{
	return FileDevice::deleteFile(filename.toLatin1().data());
}
