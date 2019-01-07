#ifndef TU_CLEANUPACTIONWIDGET_H
#define TU_CLEANUPACTIONWIDGET_H

#include <QPushButton>

#include "../Tu-common/Tu_loadinglabel.h"

class CleanupActionWidget : public QWidget
{
	Q_OBJECT
public:
	explicit CleanupActionWidget(QWidget *parent = Q_NULLPTR);
	~CleanupActionWidget();

signals:
	void sig_showDetailData();
	void sig_showMainData();
	void sig_sendClean();
	void sig_sendScan();

public slots:
	void onStartButtonClicked();
	void onCleanButtonClicked();
	void onBackButtonClicked();

	void showCleanReciveStatus(const QString &status);
	void showCleanReciveError(const QString &status);
	void showCleanOverStatus();
	void showCleanerData(const QStringList &data);
	void showCleanerStatus(const QString &status, const QString &domain);
	void showCleanerError(const QString &status);

	void displayOrgPage();
	void displayAnimation();

	void receivePolicyKitSignal(bool status);
	void accordScanOverStatusToChange(bool status);

protected:
	void initUi();
	void initLayout();
	void initConnect();
	void setLanguage();

private:
	LoadingLabel *loading_label;
	QLabel *suggest_label;
	QLabel *doing_label;

	QPushButton *scan_button;
	QPushButton *clean_button;
	QPushButton *back_button;
};

#endif // TU_CLEANUPACTIONWIDGET_H
