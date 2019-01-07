#include "Tu_mainmenu.h"
#include <QHBoxLayout>
#include <QUrl>
#include <QDesktopServices>

MainMenu::MainMenu(QWidget *parent)
	: QMenu(parent)
{
	setStyleSheet("QPushButton{ background:transparent; text-align:left; font-family: 方正黑体_GBK; font-size:13px; color:#666666; } \
				   QPushButton:hover{ color:#0396DC; }");

	initActions();
	initLayout();
	initConnect();
	setLanguage();
}

MainMenu::~MainMenu()
{

}

void MainMenu::initActions()
{
	check_widget = new QWidget;
	help_widget = new QWidget;
	feedback_widget = new QWidget;
	about_widget = new QWidget;

	check_widget_action = new QWidgetAction(this);
	help_widget_action = new QWidgetAction(this);
	feedback_widget_action = new QWidgetAction(this);
	about_widget_action = new QWidgetAction(this);

	check_label = new QLabel;
	help_label = new QLabel;
	feedback_label = new QLabel;
	about_label = new QLabel;

	check_button = new QPushButton;
	help_button = new QPushButton;
	feedback_button = new QPushButton;
	about_button = new QPushButton;

	QPixmap check_pixmap(":/res/mainmenu/upgrade.png");
	check_label->setPixmap(check_pixmap);
	check_label->setFixedSize(check_pixmap.size());
	check_button->setFocusPolicy(Qt::NoFocus);

	QPixmap help_pixmap(":/res/mainmenu/help.png");
	help_label->setPixmap(help_pixmap);
	help_label->setFixedSize(help_pixmap.size());
	help_button->setFocusPolicy(Qt::NoFocus);

	QPixmap feedback_pixmap(":/res/mainmenu/feedback.png");
	feedback_label->setPixmap(feedback_pixmap);
	feedback_label->setFixedSize(feedback_pixmap.size());
	feedback_button->setFocusPolicy(Qt::NoFocus);

	QPixmap about_pixmap(":/res/mainmenu/menu/about.png");
	about_label->setPixmap(about_pixmap);
	about_label->setFixedSize(about_pixmap.size());
	about_button->setFocusPolicy(Qt::NoFocus);
}

void MainMenu::initLayout()
{
	QHBoxLayout *check_layout = new QHBoxLayout;
	check_layout->addWidget(check_label);
	check_layout->addWidget(check_button);
	check_layout->setSpacing(10);
	check_layout->setContentsMargins(20, 0, 20, 2);
	check_widget->setLayout(check_layout);
	check_widget_action->setDefaultWidget(check_widget);

	QHBoxLayout *help_layout = new QHBoxLayout;
	help_layout->addWidget(help_label);
	help_layout->addWidget(help_button);
	help_layout->setSpacing(10);
	help_layout->setContentsMargins(20, 0, 20, 2);
	help_widget->setLayout(help_layout);
	help_widget_action->setDefaultWidget(help_widget);

	QHBoxLayout *feedback_layout = new QHBoxLayout;
	feedback_layout->addWidget(feedback_label);
	feedback_layout->addWidget(feedback_button);
	feedback_layout->setSpacing(10);
	feedback_layout->setContentsMargins(20, 0, 20, 2);
	feedback_widget->setLayout(feedback_layout);
	feedback_widget_action->setDefaultWidget(feedback_widget);

	QHBoxLayout *about_layout = new QHBoxLayout;
	about_layout->addWidget(about_label);
	about_layout->addWidget(about_button);
	about_layout->setSpacing(10);
	about_layout->setContentsMargins(20, 0, 20, 0);
	about_widget->setLayout(about_layout);
	about_widget_action->setDefaultWidget(about_widget);

	this->addAction(check_widget_action);
	this->addAction(help_widget_action);
	this->addAction(feedback_widget_action);
	this->addSeparator();
	this->addAction(about_widget_action);
}

void MainMenu::initConnect()
{
	connect(check_button, &QPushButton::clicked, this, &MainMenu::sig_showUpgradePage);
	connect(help_button, &QPushButton::clicked, this, &MainMenu::forumHelp);
	connect(feedback_button, &QPushButton::clicked, this, &MainMenu::questionFeedback);
	connect(about_button, &QPushButton::clicked, this, &MainMenu::sig_aboutUs);
}

void MainMenu::setLanguage()
{
	check_button->setText(tr("Check and update"));
	help_button->setText(tr("Forum Help"));
	feedback_button->setText(tr("Feedback"));
	about_button->setText(tr("About us"));
}

void MainMenu::forumHelp()
{
	QUrl url(QString("https://blog.csdn.net/x85371169"));
	QDesktopServices::openUrl(url);
}

void MainMenu::questionFeedback()
{
	QUrl url(QString("https://blog.csdn.net/x85371169"));
	QDesktopServices::openUrl(url);
}
