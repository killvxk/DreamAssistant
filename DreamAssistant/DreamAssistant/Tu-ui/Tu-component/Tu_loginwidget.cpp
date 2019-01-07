#include "Tu_loginwidget.h"
#include <QHBoxLayout>

LoginWidget::LoginWidget(QWidget *parent)
	: QWidget(parent)
{
	setFixedSize(300, 72);

	initUi();
	initLayout();
	initConnect();
	setLauguage();
}

LoginWidget::~LoginWidget()
{
	
}

void LoginWidget::initUi()
{
	logo_label = new QPushButton();
	logo_label->setCursor(Qt::PointingHandCursor);
	logo_label->setFocusPolicy(Qt::NoFocus);
	logo_label->setStyleSheet("background:transparent;border:0px;color:rgb(240, 240, 240);font-weight:bold;font-size:13px;");

	login_button = new QPushButton();
	login_button->setObjectName("loginButton");
	login_button->setCursor(Qt::PointingHandCursor);
	login_button->setFocusPolicy(Qt::NoFocus);
	login_button->setFixedSize(44, 44);
	login_button->setIconSize(QSize(44, 44));
	login_button->setFlat(true);

	user_label = new QLabel();
	user_label->hide();
	user_label->setStyleSheet("QLabel{color:#ffffff;font-family: 方正黑体_GBK;font-size: 12px;text-align: right;}");
	user_label->adjustSize();

	logout_btn = new QPushButton();
	logout_btn->setObjectName("whiteButton");
	logout_btn->setCursor(Qt::PointingHandCursor);
	logout_btn->setFocusPolicy(Qt::NoFocus);
	logout_btn->hide();
}

void LoginWidget::initLayout()
{
	QHBoxLayout *layout = new QHBoxLayout();
	layout->addStretch();
	layout->addWidget(logo_label, 0, Qt::AlignVCenter);
	layout->addWidget(login_button, 0, Qt::AlignVCenter);
	layout->addWidget(user_label, 0, Qt::AlignVCenter);
	layout->addWidget(logout_btn, 0, Qt::AlignVCenter);
	layout->setSpacing(11);
	layout->setMargin(0);
	layout->setContentsMargins(0, 0, 0, 0);

	setLayout(layout);
}

void LoginWidget::initConnect()
{
	connect(logo_label, &QPushButton::clicked, this, &LoginWidget::onLoginButtonClicked);
	connect(login_button, &QPushButton::clicked, this, &LoginWidget::onLoginButtonClicked);
	connect(logout_btn, &QPushButton::clicked, this, &LoginWidget::onLogoutButtonClicked);
}

void LoginWidget::showLoginInfo(QString name, QString email)
{
	logo_label->hide();
	login_button->hide();
	user_label->show();

	QString alltext = QString("%1 <%2>").arg(name).arg(email);
	QFont ft;
	QFontMetrics fm(ft);
	QString elided_text = fm.elidedText(alltext, Qt::ElideRight, 260);
	user_label->setText(elided_text);

	if (elided_text.endsWith(QStringLiteral("…")))
		user_label->setToolTip(alltext);

	logout_btn->show();
}

void LoginWidget::showLoginAndLogoutStatus(bool status)
{
	if (status) {   //logout success
		logo_label->show();
		login_button->show();
		logout_btn->hide();
		user_label->setText("");
		user_label->hide();
	} else {       //login failed

	}
}

void LoginWidget::setLauguage()
{
	logo_label->setText(tr("Login Account"));
	logout_btn->setText(tr("Logout"));
}

void LoginWidget::onLoginButtonClicked()
{
	emit sig_loginButtonClicked();
}

void LoginWidget::onLogoutButtonClicked()
{
	emit sig_logoutButtonClicked();
}

