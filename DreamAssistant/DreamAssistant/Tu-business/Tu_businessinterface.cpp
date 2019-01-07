#include "Tu_businessinterface.h"
#include <QMetaObject>
#include <QMetaEnum>
#include <QCoreApplication>

#include "Tu-device/Tu_filedevice.h"

BusinessInterface::BusinessInterface(QObject *parent)
	: QObject(parent)
{

}

BusinessInterface::~BusinessInterface()
{

}

void BusinessInterface::call(const QString &method, const QStringList &argsList)
{
	if (method.isEmpty()) {
		return;
	}

	executeCommand(method, argsList);
}

void BusinessInterface::executeCommand(const QString &method, const QStringList &argsList)
{
	QMetaObject metaObject = this->staticMetaObject;
	QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("RequestCommands"));

	switch (metaEnum.keysToValue(method.toUpper().toLatin1()))
	{
	case ONEKEY_SCAN_TRASH:
		onekey_scan_trash(argsList);
		break;
	case SCAN_TRASH:
		break;
	case CLEAN_TRASH:
		clean_transh(argsList);
		break;
	default:
		break;
	}
}

void BusinessInterface::onekey_scan_trash(const QStringList &argsList)
{
}

void BusinessInterface::clean_transh(const QStringList &argsList)
{
	
}

bool BusinessInterface::copy_file(QString filename)
{
	QString path = QCoreApplication::applicationDirPath().append("skin/custom/");

	return Singleton<FileDevice>::Instance().copyFileToPath(filename, path, true);
}

bool BusinessInterface::delete_file(QString filename)
{
	return Singleton<FileDevice>::Instance().deleteFile(filename);
}
