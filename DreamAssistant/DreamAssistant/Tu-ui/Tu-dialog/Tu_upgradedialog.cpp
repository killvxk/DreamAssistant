#include "Tu_upgradedialog.h"
#include <QDesktopServices>
#include <QMouseEvent>
#include <QUrl>

UpgradeDialog::UpgradeDialog(QWidget *parent, const QString &version, QString skin)
	: BaseDialog(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setFixedSize(334, 470);
	setStyleSheet("QDialog{border: 1px solid white;border-radius:1px;background-color: #ffffff;}");

	isBusy = false;
	upgradeOver = false;

	cur_version = version;
	cur_skin = skin;	

	initUi();
	initConnect();
	setLanuage();
}

UpgradeDialog::~UpgradeDialog()
{

}

void UpgradeDialog::initUi()
{
	baseWidget = new QWidget(this);
	baseWidget->setGeometry(QRect(0, 0, 334, 191));
	baseWidget->setAutoFillBackground(true);

	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(QPixmap(cur_skin)));
	baseWidget->setPalette(palette);

	close_btn = new PushButton(baseWidget);
	close_btn->setFocusPolicy(Qt::NoFocus);
	close_btn->loadPixmap(":/res/title/close_button.png");

	nameLabel = new QLabel(baseWidget);
	nameLabel->setAlignment(Qt::AlignCenter);
	nameLabel->setGeometry(QRect(37, 5, 260, 30));
	nameLabel->setStyleSheet("QLabel{color:#ffffff;font-family: 方正黑体_GBK;font-size: 13px;font-weight:bold;}");

	net_icon_label = new QLabel(this);
	net_icon_label->setGeometry(QRect(76, 64, 182, 181));
	net_icon_label->setStyleSheet("QLabel{background-image:url(':/res/upgrade/no-net.png')}");
	net_icon_label->hide();

	normal_icon_label = new QLabel(this);
	normal_icon_label->setAlignment(Qt::AlignCenter);
	normal_icon_label->setGeometry(QRect(76, 64, 182, 181));
	normal_icon_label->setStyleSheet("QLabel{background-image:url(':/res/upgrade/upgrade-normal.png');color:#ffffff;font-family: 方正黑体_GBK;font-size: 22px;text-align: center;}");
	normal_icon_label->hide();

	ok_icon_label = new QLabel(this);
	ok_icon_label->setGeometry(QRect(76, 64, 182, 181));
	ok_icon_label->setStyleSheet("QLabel{background-image:url(':/res/upgrade/upgrade-ok.png')}");
	ok_icon_label->hide();

	work_loading_label = new LoadingLabel(this, "working");
	work_loading_label->setGeometry(QRect(76, 64, 182, 181));
	work_loading_label->show();

	upgrade_loading_label = new LoadingLabel(this, "upgrading");
	upgrade_loading_label->setGeometry(QRect(76, 64, 182, 181));
	upgrade_loading_label->hide();

	version_label = new QLabel(this);
	version_label->setObjectName("smallgrayLabel");
	version_label->setGeometry(QRect(10, 440, 324, 20));

	doing_label = new QLabel(this);
	doing_label->setWordWrap(true);
	doing_label->setAlignment(Qt::AlignCenter);
	doing_label->setGeometry(QRect(10, 264, 324, 30));
	doing_label->setStyleSheet("QLabel{color:#000000;font-family: 方正黑体_GBK;font-size: 14px;text-align: center;}");

	error_label = new QLabel(this);
	error_label->setGeometry(QRect(10, 264, 324, 30));
	error_label->setWordWrap(true);
	error_label->setAlignment(Qt::AlignCenter);
	error_label->setStyleSheet("QLabel{color:#000000;font-family: 方正黑体_GBK;font-size: 22px;text-align: center;}");
	error_label->hide();

	tip_label = new QLabel(this);
	tip_label->setGeometry(QRect(10, 294, 324, 30));
	tip_label->setWordWrap(true);
	tip_label->setAlignment(Qt::AlignCenter);
	tip_label->setStyleSheet("QLabel{color:#999999;font-family: 方正黑体_GBK;font-size: 12px;text-align: center;}");
	tip_label->hide();

	visit_label = new QLabel(this);
	visit_label->setGeometry(QRect(10, 294, 324, 30));
	visit_label->setWordWrap(true);
	visit_label->setAlignment(Qt::AlignCenter);
	visit_label->setStyleSheet("QLabel{color:#999999;font-family: 方正黑体_GBK;font-size: 12px;text-align: center;}");

	new_widget = new QWidget(this);
	new_widget->setGeometry(QRect(17, 264, 300, 80));
	new_widget->setStyleSheet("QWidget{background:transparent; border:1px solid #3f96e4;}");
	new_widget->hide();

	official_label = new QLabel(new_widget);
	official_label->setWordWrap(true);
	official_label->setAlignment(Qt::AlignCenter);
	official_label->setGeometry(QRect(0, 15, 60, 30));
	official_label->setStyleSheet("QLabel{border:none;color:#000000;font-family: 方正黑体_GBK;font-size: 13px;text-align: center;}");

	hook_label = new QLabel(new_widget);
	hook_label->setGeometry(QRect(18, 50, 23, 16));
	hook_label->setStyleSheet("QLabel{background: transparent;border:none;background-image:url(':/res/upgrade/hook.png')}");

	vline = new QLabel(new_widget);
	vline->setGeometry(QRect(60, 0, 1, 80));
	vline->setStyleSheet("QLabel{background-color:#3f96e4;}");

	new_label = new QLabel(new_widget);
	new_label->setWordWrap(true);
	new_label->setGeometry(QRect(70, 10, 220, 30));
	new_label->setStyleSheet("QLabel{border:none;color:#000000;font-family: 方正黑体_GBK;font-size: 16px;text-align: left;}");
	
	new_num_label = new QLabel(new_widget);
	new_num_label->setWordWrap(true);
	new_num_label->setGeometry(QRect(70, 40, 220, 30));
	new_num_label->setStyleSheet("QLabel{border:none;color:#000000;font-family: 方正黑体_GBK;font-size: 16px;text-align: left;}");

	retryBtn = new QPushButton(this);
	retryBtn->setFocusPolicy(Qt::NoFocus);
	retryBtn->setGeometry(QRect(74, 350, 186, 56));
	retryBtn->setStyleSheet("QPushButton{background-image:url(':/res/upgrade/retry.png');border:0px;color:#ffffff;font-family: 方正黑体_GBK;font-size: 30px;} \
							 QPushButton:hover{background:url(':/res/upgrade/retry-hover.png');} \
							 QPushButton:pressed{background:url(':/res/upgrade/retry-press.png');}");
	retryBtn->hide();

	progressbar = new QProgressBar(this);
	progressbar->setValue(0);
	progressbar->setGeometry(QRect(30, 340, 284, 30));
	progressbar->hide();
	progressbar->setStyleSheet("QProgressBar{background-color:#ffffff;border:1px solid #aaaaaa;border-radius:0px;color:#666666;font-family: 方正黑体_GBK;}"
		                       "QProgressBar:chunk{background-color:#b1dcff;}");

	okBtn = new QPushButton(this);
	okBtn->setFocusPolicy(Qt::NoFocus);
	okBtn->setGeometry(QRect(74, 350, 186, 56));
	okBtn->setStyleSheet("QPushButton{background-image:url(':/res/upgrade/retry.png');border:0px;color:#ffffff;font-family: 方正黑体_GBK;font-size: 30px;} \
						  QPushButton:hover{background:url(':/res/upgrade/retry-hover.png');} \
						  QPushButton:pressed{background:url(':/res/upgrade/retry-press.png');}");
	okBtn->hide();
	
	upgradeBtn = new QPushButton(this);
	upgradeBtn->setFocusPolicy(Qt::NoFocus);
	upgradeBtn->setGeometry(QRect(234, 437, 91, 25));
	upgradeBtn->setObjectName("blackButton");
	upgradeBtn->hide();

	splitlabel = new QLabel(this);
	splitlabel->setGeometry(QRect(0, 430, 334, 1));
	splitlabel->setFixedHeight(1);
	splitlabel->setStyleSheet("QLabel{background:#e0e0e0;}");
}

void UpgradeDialog::initConnect()
{
	connect(close_btn, &PushButton::clicked, this, &UpgradeDialog::onCloseBtnClicked);
	connect(retryBtn, &QPushButton::clicked, this, &UpgradeDialog::onRetryBtnClicked);
	connect(upgradeBtn, &QPushButton::clicked, this, &UpgradeDialog::onUpgradeBtnClicked);
	connect(okBtn, &QPushButton::clicked, this, &UpgradeDialog::sig_close);
	connect(visit_label, &QLabel::linkActivated, this, &UpgradeDialog::openUrl);
}

void UpgradeDialog::setLanuage()
{
	setWindowTitle(tr("Check and Update"));

	nameLabel->setText(tr("Check and Update"));
	version_label->setText(tr("Current verison: ") + cur_version);
	official_label->setText(tr("Official version"));
	new_label->setText(tr("New version:"));
	error_label->setText(tr("An error occurred!"));
	tip_label->setText(tr("Network or local sources anomaly"));
	doing_label->setText(tr("Testing network and local sources..."));
	visit_label->setText(tr("you can visit the<a style='color: #3f96e4;' href = https://github.com/zhangmw1992/Dream> TU official website</a> to download the lastest deb package"));

	retryBtn->setText(tr("Retry"));
	okBtn->setText(tr("Finish"));
	upgradeBtn->setText(tr("Upgrade"));
}

void UpgradeDialog::onCloseBtnClicked()
{
	if (this->isBusy) {
		emit sig_showBackendBtn(false);
	} else if (this->upgradeOver) {
		emit sig_close();
	}

	this->close();
}

void UpgradeDialog::onRetryBtnClicked()
{
	this->isBusy = true;

	net_icon_label->hide();
	error_label->hide();
	tip_label->hide();
	retryBtn->hide();

	work_loading_label->show();
	work_loading_label->startLoading();
	doing_label->setText(tr("Testing network and local sources..."));
	doing_label->show();
	visit_label->show();
}

void UpgradeDialog::onUpgradeBtnClicked()
{
	this->isBusy = true;

	new_widget->hide();
	upgradeBtn->hide();
	normal_icon_label->hide();

	upgrade_loading_label->show();
	upgrade_loading_label->startLoading();
	doing_label->show();
	doing_label->setText(tr("Start to upgrade the main program"));
	visit_label->show();
	progressbar->setValue(0);
	progressbar->show();
}

void UpgradeDialog::openUrl(QString url)
{
	QDesktopServices::openUrl(QUrl(url));
}

void UpgradeDialog::resetTitleSkin(QString skin)
{
	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(QPixmap(cur_skin)));
	baseWidget->setPalette(palette);
}

void UpgradeDialog::checkLastestVersion()
{
	//check source list valid or not
	this->isBusy = true;
	work_loading_label->startLoading();
}

void UpgradeDialog::showErrorComponents()
{
	error_label->show();
	tip_label->show();
	retryBtn->show();

	doing_label->hide();
	visit_label->hide();
}

void UpgradeDialog::showUpdateSourceComponents()
{
	doing_label->setText(tr("Start to update the local sources"));
	visit_label->show();
	progressbar->setValue(0);
	progressbar->show();
}