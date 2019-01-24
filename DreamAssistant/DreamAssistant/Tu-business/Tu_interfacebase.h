#ifndef TU_INTERFACEBASE_H
#define TU_INTERFACEBASE_H

#include <QObject>

class InterfaceBase : public QObject
{
    Q_OBJECT
    Q_ENUMS(RequestCommands)

public:
    explicit InterfaceBase(QObject *parent = Q_NULLPTR)
        : QObject(parent) {};
    virtual ~InterfaceBase() {};

    enum RequestCommands{
        ONEKEY_SCAN_TRASH,
        SCAN_TRASH,
        CLEAN_TRASH
    };

signals:
    void sig_evt_message(QString);

    // Trash scan
    void sig_isScanning(QString);
    void sig_notifyRecycleBin(quint32, quint64);
    void sig_notifyScanDirItem(QStringList, QString, QString, qint64);
    void sig_notifyScanFinished(QString);

    // Trash clean
    void sig_notifyDeleteFile(QString, quint64);
    void sig_notifyCleanFinished(QString);

private:
    
};

#endif // TU_INTERFACEBASE_H
