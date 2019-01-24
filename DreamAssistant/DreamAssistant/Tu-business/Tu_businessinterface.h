#ifndef TU_BUSINESSINTERFACE_H
#define TU_BUSINESSINTERFACE_H

#include <QMap>
#include "Tu_interfacebase.h"
#include "Tu-pipeline/Tu_pipeline.h"

class BusinessInterface : public InterfaceBase
{
	Q_OBJECT
	
public:
	explicit BusinessInterface(QObject *parent = Q_NULLPTR);
	~BusinessInterface();

	void call(const QString &method, const QStringList &argsList);

protected:
	// Trash
	void onekey_scan_trash(const QStringList &argsList);
	void clean_transh(const QStringList &argsList);

    void interrupt_task(const QString &method);
    void interrupt_all_task();

private:
	void executeCommand(const QString &method, const QStringList &argsList);

    Pipeline *m_taskEngine;

    QMutex m_hash_mutex;
    QMap<QString, QObject *> m_hash_task;
};

#endif // TU_BUSINESSINTERFACE_H
