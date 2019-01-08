#include "Tu_titlebar.h"
#include <QMouseEvent>

TitleBar::TitleBar(QWidget *parent)
	: QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
	setFixedHeight(32);
	setAutoFillBackground(true);

	close_btn = new PushButton(this);
	close_btn->setFocusPolicy(Qt::NoFocus);
	close_btn->loadPixmap(":/res/title/close_button.png");

	title_label = new QLabel(this);
	title_label->setAlignment(Qt::AlignCenter);
	title_label->setStyleSheet("QLabel{color:#ffffff;font-family: ·½ÕýºÚÌå_GBK;font-size: 14px;text-align: center;font-weight:bold;}");

	connect(close_btn, &PushButton::clicked, this, &TitleBar::sig_closeDialog);
}

TitleBar::~TitleBar()
{

}

void TitleBar::resetBackground(QString name)
{
	backgroud_image = name;
	QPalette palette_widget;
	palette_widget.setBrush(QPalette::Background, QBrush(QPixmap(backgroud_image)));
	setPalette(palette_widget);
}

void TitleBar::resizeEvent(QResizeEvent *event)
{
	//width
	this->setFixedWidth(title_width);

	//backgrond
	QPalette palette_widget;
	palette_widget.setBrush(QPalette::Background, QBrush(QPixmap(backgroud_image)));
	setPalette(palette_widget);

	//title and font
	title_label->setText(title_content);
	title_label->setGeometry(QRect(40, 0, title_width - 80, 32));
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		if (event->y() < 5 || event->x() < 5 || rect().width() - event->x() < 5) {
			event->ignore();
			return;
		}
		press_point = event->globalPos();
		left_btn_pressed = true;
	}
	event->ignore();
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
	if (left_btn_pressed) {
		move_point = event->globalPos();
		QWidget *pMainWindow = (qobject_cast<QWidget *>(parent()));
		pMainWindow->move(pMainWindow->pos() + move_point - press_point);
		press_point = move_point;
	}
	event->ignore();
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		left_btn_pressed = false;
	}
	event->ignore();
}
