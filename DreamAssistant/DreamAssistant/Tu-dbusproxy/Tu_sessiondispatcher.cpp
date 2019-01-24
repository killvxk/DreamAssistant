#include "Tu_sessiondispatcher.h"

SessionDispatcher::SessionDispatcher(QObject *parent)
	: QObject(parent)
{
	businessInterface = new BusinessInterface(this);

	connect(businessInterface, &BusinessInterface::sig_isScanning, this, &SessionDispatcher::sig_isScanning);
	connect(businessInterface, &BusinessInterface::sig_notifyScanDirItem, this, &SessionDispatcher::sig_scanDirItem);
	connect(businessInterface, &BusinessInterface::sig_notifyRecycleBin, this, &SessionDispatcher::sig_recycleBin);
	connect(businessInterface, &BusinessInterface::sig_notifyScanFinished, this, &SessionDispatcher::sig_finishScanWork);

	connect(businessInterface, &BusinessInterface::sig_notifyDeleteFile, this, &SessionDispatcher::sig_deleteFile);
	connect(businessInterface, &BusinessInterface::sig_notifyCleanFinished, this, &SessionDispatcher::sig_finishCleanWork);
}

SessionDispatcher::~SessionDispatcher()
{

}

void SessionDispatcher::onekey_scan_function(QStringList selectedList)
{
	businessInterface->call("onekey_scan_trash", selectedList);
}

void SessionDispatcher::clean_trash_function(QStringList selectedList)
{
	businessInterface->call("clean_trash", selectedList);
}
