#include "Tu_pipeline.h"

Pipeline::Pipeline(QObject *parent)
	: QObject(parent)
{
	m_nExistingThreads = 0;
}

Pipeline::~Pipeline()
{

}

bool Pipeline::canClose()
{
	return m_nExistingThreads == 0 ? true : false;
}

int Pipeline::addThreads(int nThreads)
{
	if (nThreads >= 1 && nThreads <= 128) {
		for (int i = 0; i < nThreads; i++) {
		    WorkingThread * thread = new WorkingThread(this);
			m_vec_workingThreads.push_back(thread);

			QThread * pTh = new QThread(this);
			m_vec_InternalworkingThreads.push_back(pTh);

			thread->moveToThread(pTh);

			connect(this, &Pipeline::sig_evt_start_work, thread, &WorkingThread::FetchNewTask, Qt::QueuedConnection);
			connect(this, &Pipeline::sig_evt_stop_work, thread, &WorkingThread::setStopMark, Qt::QueuedConnection);
			connect(thread, &WorkingThread::sig_taskFinished, this, &Pipeline::on_finished_task, Qt::QueuedConnection);

			pTh->start();

			m_mutex_protect.lock();
			m_nExistingThreads++;
			m_mutex_protect.unlock();
		}
	}
	return m_vec_workingThreads.size();
}

int Pipeline::removeThreads(int nThreads)
{
	int nsz = m_vec_workingThreads.size();
	if (nThreads<0 || nThreads>nsz)
		nThreads = nsz;

	for (int i = 0; i < nThreads; i++) {
		emit sig_evt_stop_work(m_vec_workingThreads.last());
		
		m_vec_workingThreads.pop_back();
		m_vec_InternalworkingThreads.pop_back();
	}

	return m_vec_workingThreads.size();
}

TaskBase * Pipeline::popTask(bool * bValid)
{
	*bValid = false;
	TaskBase * funcres = NULL;

	m_mutex_protect.lock();
	if (m_list_tasks.empty() == false) {
		funcres = *m_list_tasks.begin();
		m_list_tasks.pop_front();
		*bValid = true;
	}
	m_mutex_protect.unlock();

	return funcres;
}

void Pipeline::pushTask(TaskBase * task, bool bFire)
{
	m_mutex_protect.lock();
	m_list_tasks.push_back(task);
	task->addRef();
	m_mutex_protect.unlock();

	int nsz = m_vec_workingThreads.size();
	if (bFire == true) {
		for (int i = 0; i < nsz; i++) {
			if (m_vec_workingThreads[i]->m_bBusy == false) {
				on_finished_task(m_vec_workingThreads[i]);
				break;
			}
		}
	}
}

int Pipeline::threadsCount()
{
	return m_vec_workingThreads.size();
}

int Pipeline::payload()
{
	int res = 0;

	m_mutex_protect.lock();
	res = m_list_tasks.size();
	m_mutex_protect.unlock();

	return res;
}

int Pipeline::idleThreads()
{
	int idle = 0;
	int nsz = m_vec_workingThreads.size();

	for (int i = 0; i < nsz; i++) {
		if (m_vec_workingThreads[i]->m_bBusy == false)
			idle++;
	}

	return idle;
}

void Pipeline::on_finished_task(WorkingThread * task)
{
	int res = 0;

	m_mutex_protect.lock();
	res = m_list_tasks.size();
	m_mutex_protect.unlock();

	if (res) {
		emit sig_evt_start_work(task);
	}
}
