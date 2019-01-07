#include "Tu_homepage.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>

HomePage::HomePage(QWidget *parent, const QString &version)
	: QWidget(parent)
{
	setFixedSize(900, 326);
	setAutoFillBackground(true);

	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(Qt::white));
	setPalette(palette);

	current_version = version;

	initUi();
	initLayout();
	initConnect();
	setLanguage();
}

HomePage::~HomePage()
{
	
}

void HomePage::initUi()
{
	version_logo = new QLabel;
	version_title = new QLabel;
	version_tip = new QLabel;

	check_btn = new QPushButton;
	check_btn->hide();

	box_logo = new QLabel;
	box_title = new QPushButton;
	box_title->setFixedWidth(200);
	box_title->setCursor(Qt::PointingHandCursor);
	box_title->setFocusPolicy(Qt::NoFocus);
	box_title->setStyleSheet("QPushButton{background:transparent;text-align:left;font-family: 方正黑体_GBK;font-size:24px;color:#000000;}QPushButton:hover{color:#3f96e4;}");

	box_tip = new QLabel;

	check_btn->setStyleSheet("QPushButton{background:transparent;font-family: 方正黑体_GBK;font-size:12px;color:#3f96e4;}QPushButton:hover{color:#3f96e4;}");
	check_btn->setCursor(Qt::PointingHandCursor);
	check_btn->setFocusPolicy(Qt::NoFocus);

	version_title->setFixedHeight(30);
	version_title->setObjectName("bigblackLabel");

	version_tip->setAlignment(Qt::AlignLeft);
	version_tip->setObjectName("smallgrayLabel");
	version_tip->setFixedWidth(380);

	box_tip->setAlignment(Qt::AlignLeft);
	box_tip->setObjectName("smallgrayLabel");

	version_tip->setWordWrap(true);
	box_tip->setWordWrap(true);
	box_tip->setFixedWidth(380);

	version_logo->setFixedSize(65, 65);
	version_logo->setPixmap(QPixmap(":/res/home/version.png"));

	box_logo->setFixedSize(65, 65);
	box_logo->setPixmap(QPixmap(":/res/home/box.png"));
}

void HomePage::initLayout()
{
	QHBoxLayout *layout1 = new QHBoxLayout;
	layout1->addWidget(version_title);
	layout1->addWidget(check_btn);
	layout1->addStretch();
	layout1->setMargin(0);
	layout1->setSpacing(5);
	layout1->setContentsMargins(0, 0, 0, 0);

	QVBoxLayout *layout2 = new QVBoxLayout;
	layout2->addStretch();
	layout2->addLayout(layout1);
	layout2->addWidget(version_tip);
	layout2->addStretch();
	layout2->setMargin(0);
	layout2->setSpacing(5);
	layout2->setContentsMargins(0, 0, 0, 0);

	QHBoxLayout *layout3 = new QHBoxLayout;
	layout3->addWidget(version_logo);
	layout3->addLayout(layout2);
	layout3->addStretch();
	layout3->setMargin(0);
	layout3->setSpacing(5);
	layout3->setContentsMargins(0, 0, 0, 0);

	QVBoxLayout *layout4 = new QVBoxLayout;
	layout4->addStretch();
	layout4->addWidget(box_title);
	layout4->addWidget(box_tip);
	layout4->addStretch();
	layout4->setMargin(0);
	layout4->setSpacing(5);
	layout4->setContentsMargins(0, 0, 0, 0);

	QStringList icon_list;
	icon_list << ":/res/home/living.png" << ":/res/home/playback.png" << ":/res/home/more.png";
	QStringList text_list;
	text_list << tr("Living") << tr("Music") << tr("More");

	QHBoxLayout *button_layout = new QHBoxLayout;
	QSignalMapper *signal_mapper = new QSignalMapper(this);
	for (int i = 0; i < icon_list.size(); i++) {
		MapButton *map_button = new MapButton;
		map_button->setFocusPolicy(Qt::NoFocus);
		map_button->setIcon(icon_list.at(i));
		map_button->setText(text_list.at(i));
		connect(map_button, &MapButton::clicked, signal_mapper, static_cast<void(QSignalMapper::*)(void)>(&QSignalMapper::map));
		signal_mapper->setMapping(map_button, QString::number(i, 10));
		button_layout->addWidget(map_button);
	}
	connect(signal_mapper, static_cast<void(QSignalMapper::*)(const QString &)>(&QSignalMapper::mapped), this, &HomePage::switchPageIndex);

	QHBoxLayout *layout5 = new QHBoxLayout();
	layout5->addWidget(box_logo);
	layout5->addLayout(layout4);
	layout5->addStretch();
	layout5->addLayout(button_layout);
	layout5->setMargin(0);
	layout5->setSpacing(5);
	layout5->setContentsMargins(0, 0, 0, 0);

	QVBoxLayout *main_layout = new QVBoxLayout();
	main_layout->addLayout(layout3);
	main_layout->addLayout(layout5);
	main_layout->setMargin(0);
	main_layout->setSpacing(50);
	main_layout->setContentsMargins(60, 50, 60, 80);

	setLayout(main_layout);
}

void HomePage::initConnect()
{
	connect(box_title, &QPushButton::clicked, this, &HomePage::sig_sendSignal);
	connect(check_btn, &QPushButton::clicked, this, &HomePage::onCheckBtnClicked);
}

void HomePage::setLanguage()
{
	version_title->setText(tr("Current Version Number") + "  " + current_version);
	version_tip->setText(tr("Update to the lastest version, make it work better"));
	check_btn->setText(tr("updating on the backend"));
	box_title->setText(tr("Common toolbox"));
	box_tip->setText(tr("Fast and practical, making the system more personalized"));
}

void HomePage::onCheckBtnClicked()
{
	emit sig_sendOpenUpgrade();

	check_btn->hide();
}

void HomePage::displayBackedBtn(bool flag)
{
	if (flag)
		check_btn->setText(tr("Upgrade is complete"));
	else
		check_btn->setText(tr("Updating on the backend"));

	check_btn->show();
}

void HomePage::hideBackedBtn()
{
	check_btn->hide();
}

void HomePage::switchPageIndex(QString index)
{
	if (index == "0")
		emit sig_sendSubIndex(0);
	else if (index == "1")
		emit sig_sendSubIndex(1);
	else if (index == "2") {
		emit sig_moreSignal();
	}
}