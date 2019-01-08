#include "Tu_msgbox.h"
#include <QPainter>

MsgBox::MsgBox(QWidget *parent, QString skin)
	: BaseDialog(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
	setFixedSize(320, 180);

    baseWidget = new QWidget(this);
    baseWidget->setGeometry(QRect(0, 0, 320, 36));
    baseWidget->setAutoFillBackground(true);

    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(skin)));
    baseWidget->setPalette(palette);

    initUi();
    initConnect();
}

MsgBox::~MsgBox()
{

}

void MsgBox::initUi()
{
    close_button = new PushButton(baseWidget);
    close_button->setFocusPolicy(Qt::NoFocus);
    close_button->loadPixmap(":/res/title/close_button.png");

    title_label = new QLabel(baseWidget);
    title_label->setGeometry(QRect(100, 0, 120, 36));
    title_label->setStyleSheet("QLabel{color:#ffffff;font-family: 方正黑体_GBK;font-size: 13px;font-weight:bold;}");
    title_label->setAlignment(Qt::AlignCenter);

    ok_button = new QPushButton(this);
    cancel_button = new QPushButton(this);

    msg_label = new QLabel(this);
    msg_label->setGeometry(20, 65, 45, 45);
    msg_label->setScaledContents(true);

    ask_label = new QLabel(this);
    ask_label->setWordWrap(true);
    ask_label->setGeometry(80, 65, 220, 40);

    ok_button->setGeometry(160, 135, 60, 25);
    cancel_button->setGeometry(240, 135, 60, 25);
}

void MsgBox::initConnect()
{
    connect(ok_button, &QPushButton::clicked, this, &MsgBox::okOperate);
    connect(close_button, &PushButton::clicked, this, &MsgBox::cancelOperate);
    connect(cancel_button, &QPushButton::clicked, this, &MsgBox::cancelOperate);
}

void MsgBox::setInfo(QString title_info, QString info, QPixmap pixmap, bool is_ok_hidden)
{
	title_label->setText(title_info);
	ask_label->setText(info);
	msg_label->setPixmap(pixmap);

	ok_button->setHidden(is_ok_hidden);
	if (is_ok_hidden) {
		cancel_button->setText(tr("Ok"));
	} else {
		ok_button->setText(tr("Ok"));
		cancel_button->setText(tr("Cancel"));
	}
}

void MsgBox::okOperate()
{
	this->accept();
}

void MsgBox::cancelOperate()
{
	this->reject();
}
