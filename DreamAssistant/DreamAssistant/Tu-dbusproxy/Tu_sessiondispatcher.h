#ifndef TU_SESSIONDISPATCHER_H
#define TU_SESSIONDISPATCHER_H

#include <QObject>

#include "../Tu-business/Tu_businessinterface.h"

class SessionDispatcher : public QObject
{
	Q_OBJECT
public:
	explicit SessionDispatcher(QObject *parent = Q_NULLPTR);
	~SessionDispatcher();

	void onekey_scan_function(QStringList selectedList);
	void clean_trash_function(QStringList selectedList);

signals:
	void sig_isScanning(QString msg);
	void sig_scanDirItem(QStringList, QString, QString, quint64);
	void sig_recycleBin(quint32, quint64);
	void sig_finishScanWork(QString);

	void sig_deleteFile(QString, quint64);
	void sig_finishCleanWork(QString);

private:
	BusinessInterface *businessInterface;
};

#endif // TU_SESSIONDISPATCHER_H
