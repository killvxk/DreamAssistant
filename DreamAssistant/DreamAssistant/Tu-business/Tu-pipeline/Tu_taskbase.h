#ifndef TU_TASKBASE_H
#define TU_TASKBASE_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>

class TaskBase : public QObject
{
	Q_OBJECT
public:
	explicit TaskBase(QObject *parent = Q_NULLPTR);
	~TaskBase();

	virtual int run() = 0;

	int addRef();
	int delRef();

	int ref();

	bool LockRun();
	void UnlockRun();

    bool bTermSet;

private:
	int refCount;

	QMutex m_mutex_ref;
	QMutex m_mutex_run;
};

#endif // TU_TASKBASE_H
