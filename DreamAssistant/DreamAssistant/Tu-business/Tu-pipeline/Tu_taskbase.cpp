#include "Tu_taskbase.h"

TaskBase::TaskBase(QObject *parent)
	: QObject(parent)
{
	refCount = 0;
}

TaskBase::~TaskBase()
{

}

int TaskBase::addRef()
{
	QMutexLocker locker(&m_mutex_ref);
	refCount++;

	return refCount;
}

int TaskBase::delRef()
{
	QMutexLocker locker(&m_mutex_ref);
	refCount--;

	return refCount;
}

int TaskBase::ref()
{
	QMutexLocker locker(&m_mutex_ref);

	return refCount;
}

bool TaskBase::LockRun()
{
	return m_mutex_run.tryLock();
}

void TaskBase::UnlockRun()
{
	return m_mutex_run.unlock();
}