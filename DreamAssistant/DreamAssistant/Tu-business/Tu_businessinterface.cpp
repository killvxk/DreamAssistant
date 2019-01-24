#include "Tu_businessinterface.h"
#include "Tu-core/Tu_define.h"
#include <QMetaObject>
#include <QMetaEnum>
#include <QCoreApplication>

#include "Tu_trashscan.h"
#include "Tu_trashclean.h"

BusinessInterface::BusinessInterface(QObject *parent)
	: InterfaceBase(parent)
{
    m_taskEngine = new Pipeline(this);
    m_taskEngine->addThreads(TASK_THREAD_NUMBER);
}

BusinessInterface::~BusinessInterface()
{
    interrupt_all_task();

    m_taskEngine->removeThreads(-1);
    while (m_taskEngine->canClose() == false) {
        QCoreApplication::processEvents();
        QThread::currentThread()->msleep(200);
    }
    m_taskEngine->deleteLater();
}

void BusinessInterface::call(const QString &method, const QStringList &argsList)
{
	if (method.isEmpty()) {
		return;
	}

	executeCommand(method, argsList);
}

void BusinessInterface::executeCommand(const QString &method, const QStringList &argsList)
{
	QMetaObject metaObject = this->staticMetaObject;
	QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("RequestCommands"));

	switch (metaEnum.keysToValue(method.toUpper().toLatin1()))
	{
	case ONEKEY_SCAN_TRASH:
		onekey_scan_trash(argsList);
		break;
	case SCAN_TRASH:
		break;
	case CLEAN_TRASH:
		clean_transh(argsList);
		break;
	default:
		break;
	}
}

void BusinessInterface::onekey_scan_trash(const QStringList &argsList)
{
    TrashScan *trashScan = NULL;

    m_hash_mutex.lock();
    bool nHashContains = (m_hash_task.find("onekey_scan_trash") != m_hash_task.end()) ? true : false;

    if (nHashContains == false) {
        trashScan = new TrashScan;
        connect(trashScan, &TrashScan::notifyCurrentScanDir, this, &BusinessInterface::sig_isScanning, Qt::QueuedConnection);
        connect(trashScan, &TrashScan::notifyScanDirItem, this, &BusinessInterface::sig_notifyScanDirItem, Qt::QueuedConnection);
        connect(trashScan, &TrashScan::notifyRecycleBin, this, &BusinessInterface::sig_notifyRecycleBin, Qt::QueuedConnection);
        connect(trashScan, &TrashScan::notifyScanFinished, this, &BusinessInterface::sig_notifyScanFinished, Qt::QueuedConnection);

        m_hash_task["onekey_scan_trash"] = trashScan;
    } else {
        emit sig_evt_message("sacning");
        return;
    }

    bool nblocks = trashScan->oneKeyScan();
    if (nblocks) {
        m_taskEngine->pushTask(trashScan);
    }

    m_hash_mutex.unlock();
}

void BusinessInterface::clean_transh(const QStringList &argsList)
{
    TrashClean *trashClean = NULL;

    m_hash_mutex.lock();
    bool nHashContains = (m_hash_task.find("clean_trash") != m_hash_task.end()) ? true : false;

    if (nHashContains == false) {
        trashClean = new TrashClean;
        connect(trashClean, &TrashClean::notifyDeleteFile, this, &BusinessInterface::sig_notifyDeleteFile, Qt::QueuedConnection);
        connect(trashClean, &TrashClean::notifyCleanFinished, this, &BusinessInterface::sig_notifyCleanFinished, Qt::QueuedConnection);

        m_hash_task["clean_trash"] = trashClean;
    } else {
        emit sig_evt_message("cleaning");
        return;
    }

    bool nblocks = trashClean->cleanTrash();
    if (nblocks) {
        m_taskEngine->pushTask(trashClean);
    }

    m_hash_mutex.unlock();
}

void BusinessInterface::interrupt_task(const QString &method)
{
    TaskBase *task = NULL;

    m_hash_mutex.lock();

    bool nHashContains = (m_hash_task.find(method) != m_hash_task.end()) ? true : false;
    if (nHashContains)
        task = static_cast<TaskBase *>(m_hash_task[method]);

    if (task) {
        m_hash_task.remove(method);
        task->bTermSet = true;
    }

    m_hash_mutex.unlock();
}

void BusinessInterface::interrupt_all_task()
{
    TaskBase *task = NULL;

    m_hash_mutex.lock();

    QMap<QString, QObject *>::iterator itor = m_hash_task.begin();
    for (; itor != m_hash_task.end();) {
        task = static_cast<TaskBase *>(itor.value());

        if (task) {
            m_hash_task.erase(itor++);
            task->bTermSet = true;
        }
    }

    m_hash_mutex.unlock();
}
