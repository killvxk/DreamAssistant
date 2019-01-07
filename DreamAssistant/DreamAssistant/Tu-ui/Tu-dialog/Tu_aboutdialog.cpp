#include "Tu_aboutdialog.h"
#include <QPropertyAnimation>

AboutDialog::AboutDialog(QWidget *parent, const QString &ver, QString skin)
	: BaseDialog(parent)
	, version(ver)
{
	setWindowFlags(Qt::FramelessWindowHint);
	setFixedSize(442, 326);
	setStyleSheet("QDialog{border: 1px solid white;border-radius:1px;background-color: #ffffff;}");

	aboutGroup = NULL;
	contributorGroup = NULL;
	cur_skin = skin;

	initUi();
	initAnimation();
	initConnect();
	setLanguage();
}

AboutDialog::~AboutDialog()
{

}

void AboutDialog::initUi()
{
	baseWidget = new QWidget(this);
	baseWidget->setGeometry(QRect(0, 0, 442, 82));
	baseWidget->setAutoFillBackground(true);

	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(QPixmap(cur_skin)));
	baseWidget->setPalette(palette);

	close_btn = new PushButton(baseWidget);
	close_btn->setFocusPolicy(Qt::NoFocus);
	close_btn->loadPixmap(":/res/title/close_button.png");

	iconLabel = new QLabel(baseWidget);
	iconLabel->setGeometry(QRect(380, 20, 44, 44));

	nameLabel = new QLabel(baseWidget);
	nameLabel->setGeometry(QRect(71, 5, 300, 30));

	QImage image(":/res/aboutus/dream.png");
	image = image.scaled(QSize(44, 44), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	iconLabel->setPixmap(QPixmap::fromImage(image));

	nameLabel->setStyleSheet("QLabel{color:#ffffff;font-family: 方正黑体_GBK;font-size: 13px;font-weight:bold;}");
	nameLabel->setAlignment(Qt::AlignCenter);

	aboutBtn = new QPushButton(baseWidget);
	aboutBtn->setGeometry(QRect(10, 50, 60, 24));

	contributorBtn = new QPushButton(baseWidget);
	contributorBtn->setGeometry(QRect(75, 50, 80, 24));

	indicator = new QLabel(baseWidget);
	indicator->setStyleSheet("QLabel{background-image:url(':/res/aboutus/underline.png');background-position:center;}");
	indicator->setGeometry(QRect(10, 75, 60, 2));

	aboutEdit = new QTextBrowser(this);
	aboutEdit->setOpenLinks(true);
	aboutEdit->setOpenExternalLinks(true);
	aboutEdit->setFocusPolicy(Qt::NoFocus);
	aboutEdit->setGeometry(QRect(17, 92, 408, 200));

	contributorEdit = new QTextEdit(this);
	contributorEdit->setFocusPolicy(Qt::NoFocus);
	contributorEdit->setGeometry(QRect(17, 92, 408, 200));

	aboutEdit->setReadOnly(true);
	contributorEdit->setReadOnly(true);

	contributorEdit->hide();

	aboutBtn->setFocusPolicy(Qt::NoFocus);
	aboutBtn->setObjectName("transparentButton");

	contributorBtn->setFocusPolicy(Qt::NoFocus);
	contributorBtn->setObjectName("transparentButton");

	aboutBtn->setStyleSheet("QPushButton{background:transparent;font-family: 方正黑体_GBK;font-size:14px;color:#ffffff;}");
	contributorBtn->setStyleSheet("QPushButton{background:transparent;font-family: 方正黑体_GBK;font-size:14px;color:#ffffff;}");

	aboutEdit->setStyleSheet("QTextBrowser{border:none;font-family: 方正黑体_GBK;font-size:14px;}");
	contributorEdit->setStyleSheet("QTextEdit{border:none;font-family: 方正黑体_GBK;font-size:14px;}");

	okBtn = new QPushButton(this);
	okBtn->setGeometry(QRect(334, 290, 90, 25));
	okBtn->setObjectName("blackButton");
	okBtn->setFocusPolicy(Qt::NoFocus);
}

void AboutDialog::initAnimation()
{
	QRect mainAcitonRect(10, 75, 60, 2);
	QRect origAcitonRect(75, 75, 80, 2);

	QPropertyAnimation *aboutAnimation = new QPropertyAnimation(indicator, "geometry");
	aboutAnimation->setDuration(300);
	aboutAnimation->setStartValue(origAcitonRect);
	aboutAnimation->setEndValue(mainAcitonRect);

	aboutGroup = new QParallelAnimationGroup(this);
	aboutGroup->addAnimation(aboutAnimation);

	QPropertyAnimation *contributorAnimation = new QPropertyAnimation(indicator, "geometry");
	contributorAnimation->setDuration(300);
	contributorAnimation->setStartValue(mainAcitonRect);
	contributorAnimation->setEndValue(origAcitonRect);

	contributorGroup = new QParallelAnimationGroup(this);
	contributorGroup->addAnimation(contributorAnimation);
}

void AboutDialog::initConnect()
{
	connect(aboutBtn, &QPushButton::clicked, this, &AboutDialog::onAboutBtnClicked);
	connect(contributorBtn, &QPushButton::clicked, this, &AboutDialog::onContributorBtnClicked);
	connect(close_btn, &PushButton::clicked, this, &AboutDialog::close);
	connect(okBtn, &QPushButton::clicked, this, &AboutDialog::close);
}

void AboutDialog::onAboutBtnClicked()
{
	aboutGroup->start();
	aboutEdit->show();
	contributorEdit->hide();
}

void AboutDialog::onContributorBtnClicked()
{
	contributorGroup->start();
	contributorEdit->show();
	aboutEdit->hide();
}

void AboutDialog::resetTitleSkin(QString skin)
{
	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(QPixmap(skin)));
	baseWidget->setPalette(palette);
}

void AboutDialog::setLanguage()
{
	setWindowTitle(tr("About Us"));
	
	nameLabel->setText(tr("Dream Assisant") + " " + version);
	aboutBtn->setText(tr("About"));
	contributorBtn->setText(tr("Contributor"));

	aboutEdit->setText(QString("<html><style type=\"text/css\">p{line-height:18px; text-indent:32px;}</style><body><p>%1</p><p>%2</p><p>%3</p></body></html>")
					   .arg(tr("Dream Assistant is a powerful online learning software developed by Mr.Zhang.Mainly for the naive user, it can help users manage the system.At present, It provides system junk scanning and cleaning, and some other functions."))
					   .arg(tr("The software is still under development.Please visit <a style='color: #3f96e4;' href=\"https://blog.csdn.net/x85371169\">blog.csdn.net</a> for more information. Welcome everyone to join with us."))
					   .arg(tr("Dream-assistant Homepage: <a style='color: #3f96e4;' href=\"https://github.com/zhangmw1992/Dream\">https://github.com</a>")));

	contributorEdit->setText(tr("Maintainer:\n\r    Mr.zhang <13699133727@163.com>"));

	okBtn->setText(tr("Close"));
}
