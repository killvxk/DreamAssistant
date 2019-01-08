#ifndef TU_WORKINGTHREAD_H
#define TU_WORKINGTHREAD_H

#include <QObject>

#include "Tu_taskbase.h"

class Pipeline;
class WorkingThread : public QObject
{
	Q_OBJECT
public:
	explicit WorkingThread(Pipeline * pipl, QObject *parent = Q_NULLPTR);
	~WorkingThread();

	bool m_bBusy;

signals:
	void sig_taskFinished(WorkingThread *);

public slots:
	void setStopMark(WorkingThread *);
	void FetchNewTask(WorkingThread *);

protected:
	Pipeline * m_pipeline;

	bool m_bRuning;
};

#endif // TU_WORKINGTHREAD_H
