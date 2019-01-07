#ifndef TU_CLEANUPAGE_H
#define TU_CLEANUPAGE_H

#include <QStackedWidget>

class CleanupPage : public QWidget
{
	Q_OBJECT
public:
	explicit CleanupPage(QWidget *parent = Q_NULLPTR);
	~CleanupPage();

	void resetSkin(QString skin);

	void initUi(QString skin);

signals:
	void sig_transClean();
	void sig_transScan();
	void sig_clearDetailPage();
	void sig_tranActionAnimaiton();
	void sig_tranScanOver(bool status);

public slots:
	void displayDetailPage();
	void displayMainPage();

private:
	QStackedWidget *statked_widget;
};

#endif // TU_CLEANUPAGE_H
