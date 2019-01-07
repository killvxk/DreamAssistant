#ifndef TU_HOMEPAGE_H
#define TU_HOMEPAGE_H

#include <QLabel>
#include <QPushButton>

#include "../Tu-common/Tu_mapbutton.h"

class HomePage : public QWidget
{
	Q_OBJECT
public:
	explicit HomePage(QWidget *parent = Q_NULLPTR, const QString &version = "");
	~HomePage();

signals:
	void sig_sendSubIndex(int index);
	void sig_sendSignal();
	void sig_moreSignal();
	void sig_sendOpenUpgrade();

public slots:
	void switchPageIndex(QString index);
	void displayBackedBtn(bool flag);
	void onCheckBtnClicked();
	void hideBackedBtn();

protected:
	void initUi();
	void initLayout();
	void initConnect();
	void setLanguage();

private:
	QLabel *version_logo;
	QLabel *version_title;
	QLabel *version_tip;

	QPushButton *check_btn;

	QLabel *box_logo;
	QPushButton *box_title;
	QLabel *box_tip;

	QString current_version;
};

#endif // TU_HOMEPAGE_H
