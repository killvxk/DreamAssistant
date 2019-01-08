#ifndef TU_PIPELINE_H
#define TU_PIPELINE_H

#include <QVector>
#include <QThread>

#include "Tu_workingthread.h"
#include "Tu_taskbase.h"

class Pipeline : public QObject
{
	Q_OBJECT
	friend class WorkingThread;
public:
	explicit Pipeline(QObject *parent = Q_NULLPTR);
	~Pipeline();

	int addThreads(int nThreads);

	//remove n threads and kill them.nthreads=-1 means kill all.
	int removeThreads(int nThreads);
	int threadsCount();
	int payload();
	int idleThreads();

	bool canClose();

signals:
	void sig_evt_start_work(WorkingThread * task);
	void sig_evt_stop_work(WorkingThread * task);

public slots:
	void on_finished_task(WorkingThread * task);

	void pushTask(TaskBase *task, bool bFire = true);

protected:
	QMutex m_mutex_protect;

	//vworking threads
	QVector<WorkingThread *> m_vec_workingThreads;
	QVector<QThread *> m_vec_InternalworkingThreads;

	//vThis is a C++11 function pool.
	//vreturn -1,the function will be kept in list, return 0 , will be removed.
	std::list<TaskBase *> m_list_tasks;

	int m_nExistingThreads;

protected:
	//vThreads call this function to get next task, task will be popped from list.
	TaskBase * popTask(bool * bValid);	
};

#endif // TU_PIPELINE_H
