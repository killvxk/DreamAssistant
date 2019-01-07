#ifndef TU_HOMEACTIONWIDGET_H
#define TU_HOMEACTIONWIDGET_H

#include <QSettings>
#include <QPushButton>

#include "../Tu-common/Tu_loadinglabel.h"

class MainWindow;
class SessionDispatcher;
class SystemDispatcher;

class HomeActionWidget : public QWidget
{
	Q_OBJECT
public:
	explicit HomeActionWidget(QWidget *parent = Q_NULLPTR, QSettings *mSettings = NULL);
	~HomeActionWidget();

	void setParentWindow(MainWindow* window) { p_mainwindow = window; }
	void setSessionDbusProxy(SessionDispatcher* dispatcher) { sessionProxy = dispatcher; }
	void setSystemDbusProxy(SystemDispatcher* dispatcher) { systemProxy = dispatcher; }

	void enableScanButton();

public slots:
	void onStartButtonClicked();
	void onCleanButtonClicked();
	void onEndButtonClicked();

	void getScanResult(QString msg);
	void getScanDirItem(QStringList, QString, QString, quint64);
	void getRecycleBin(quint32, quint64);
	void finishScanResult(QString msg);

	void getCleaningMessage(QString msg, quint64 size);
	void finishCleanResult(QString msg);

protected:
	void initUi();
	void initLayout();
	void initConnect();
	void setLanguage();

	void writeFixCleanDate();
	void writeSafeScanDate();

	QString getFixCleanDate();
	QString getCurrentDateTime();
	QString getSafeScanDate();
	QString getOneKeyFlag();

private:
	LoadingLabel *loading_label;
	QLabel *suggest_label;
	QLabel *scan_result_label;
	QLabel *result_label;
	QLabel *doing_label;

	QPushButton *scan_button;
	QPushButton *clean_button;
	QPushButton *back_button;

	QString dateStr;
	QString workFlag;
	QString scanFinishTime;

	QSettings *pSettings;

	quint64 m_trashSize;
	quint64 m_clearSize;

	MainWindow *p_mainwindow;
	SystemDispatcher *systemProxy;
	SessionDispatcher *sessionProxy;
};

#endif // TU_HOMEACTIONWIDGET_H
