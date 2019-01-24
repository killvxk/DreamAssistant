#include "Tu_workingthread.h"
#include "Tu_pipeline.h"

WorkingThread::WorkingThread(Pipeline * pipl, QObject *parent)
	: QObject(parent)
{
	m_bRuning = true;
	m_bBusy = false;

	m_pipeline = pipl;
}

WorkingThread::~WorkingThread()
{

}

void WorkingThread::setStopMark(WorkingThread * obj)
{
	if (obj != this) {
		return;
	}

	m_bRuning = false;

	m_pipeline->m_mutex_protect.lock();
	m_pipeline->m_nExistingThreads--;
	m_pipeline->m_mutex_protect.unlock();

	this->deleteLater();
    QThread::currentThread()->quit();  
}

void WorkingThread::FetchNewTask(WorkingThread * obj)
{
	if (obj != this)
		return;

	if (m_bRuning) {
		bool bValid = false;
		TaskBase * ptr = m_pipeline->popTask(&bValid);

		if (bValid == true && ptr != NULL) {
			m_bBusy = true;

			if (ptr->LockRun() == true) {
				int res = ptr->run();
				ptr->delRef();
				if (res != 0)
					m_pipeline->pushTask(ptr, false);
				ptr->UnlockRun();
			} else {
				ptr->delRef();
				m_pipeline->pushTask(ptr, false);
			}
			m_bBusy = false;
		}

		emit sig_taskFinished(this);
	}
}