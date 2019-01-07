#ifndef TU_BUSINESSINTERFACE_H
#define TU_BUSINESSINTERFACE_H

#include <QObject>

class BusinessInterface : public QObject
{
	Q_OBJECT
	Q_ENUMS(RequestCommands)
public:
	explicit BusinessInterface(QObject *parent = Q_NULLPTR);
	~BusinessInterface();

	enum RequestCommands{
		ONEKEY_SCAN_TRASH,
		SCAN_TRASH,
		CLEAN_TRASH
	};

	void call(const QString &method, const QStringList &argsList);

	// trash
	void onekey_scan_trash(const QStringList &argsList);
	void clean_transh(const QStringList &argsList);

	// skin
	bool copy_file(QString filename);
	bool delete_file(QString filename);

signals:
	void sig_evt_message(QString);

	void sig_isScanning(QString);
	void sig_notifyRecycleBin(quint32, quint64);
	void sig_notifyScanDirItem(QStringList, QString, QString, qint64);
	void sig_notifyScanFinished(QString);

	void sig_notifyDeleteFile(QString, quint64);
	void sig_notifyCleanFinished(QString);

private:
	void executeCommand(const QString &method, const QStringList &argsList);

};

#endif // TU_BUSINESSINTERFACE_H
