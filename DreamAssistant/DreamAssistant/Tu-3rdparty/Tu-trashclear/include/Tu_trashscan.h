#ifndef TU_TRASHSCAN_H
#define TU_TRASHSCAN_H

#include "trashclear_global.h"
#include "./Tu-common/Tu_scandirinfo.h"
#include "../Tu-pipeline/Tu_taskbase.h"

class TRASHCLEAR_EXPORT TrashScan : public TaskBase
{
	Q_OBJECT
public:
	explicit TrashScan(QObject *parent = Q_NULLPTR);
	~TrashScan();

	bool oneKeyScan();

signals:
	void notifyScanFinished(QString);
	void notifyRecycleBin(quint32, quint64);
	void notifyCurrentScanDir(QString);  // 通知当前正在查找的目录
	void notifyScanDirItem(QStringList, QString, QString, quint64); 

protected:
	int run();

	bool findFileInDirectory(const ScanDirInfo& info);
	bool findFileWithExtInDirectory(QString path, QStringList strExtArray, QStringList strFilt, int index, QString FriendName);

	QStringList getSubDir(QString path);
	quint64 calculatedSize(QString path, QStringList fiels);

private:
	QMutex m_mutex_rawData;
	QList<ScanDirInfo> m_list_RawData;
};

#endif // TU_TRASHSCAN_H
