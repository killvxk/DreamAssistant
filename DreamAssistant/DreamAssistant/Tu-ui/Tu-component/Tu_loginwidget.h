#ifndef TU_LOGINWIDGET_H
#define TU_LOGINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class LoginWidget : public QWidget
{
	Q_OBJECT
public:
	explicit LoginWidget(QWidget *parent = Q_NULLPTR);
	~LoginWidget();

signals:
	void sig_loginButtonClicked();
	void sig_logoutButtonClicked();

public slots:
	void onLoginButtonClicked();
	void onLogoutButtonClicked();
	void showLoginInfo(QString name, QString email);
	void showLoginAndLogoutStatus(bool status);

protected:
	void initUi();
	void initLayout();
	void initConnect();
	void setLauguage();

private:
	QPushButton *login_button;
	QPushButton *logo_label;
	QPushButton *logout_btn;

	QLabel *user_label;
};

#endif // TU_LOGINWIDGET_H
