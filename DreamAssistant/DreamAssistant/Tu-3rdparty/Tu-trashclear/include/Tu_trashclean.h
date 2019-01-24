#ifndef TU_TRASHCLEAN_H
#define TU_TRASHCLEAN_H

#include "trashclear_global.h"
#include "./Tu-common/Tu_scandirinfo.h"
#include "../Tu-pipeline/Tu_taskbase.h"

class TRASHCLEAR_EXPORT TrashClean : public TaskBase
{
	Q_OBJECT
public:
	explicit TrashClean(QObject *parent = Q_NULLPTR);
	~TrashClean();

	bool cleanTrash();

signals:
	void notifyCleanFinished(QString);
	void notifyDeleteFile(QString, quint64);

protected:
	int run();

private:
	QMutex m_mutex_rawData;
	QList<ScanDirInfo> m_list_RawData;
};

#endif // TU_TRASHCLEAN_H
