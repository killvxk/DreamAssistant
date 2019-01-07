#include "Tu_pushbutton.h"
#include <QMouseEvent>
#include <QPainter>

PushButton::PushButton(QWidget *parent)
	: QPushButton(parent)
{
	status = NORMAL;
	mouse_press = false;
}

PushButton::~PushButton()
{

}

void PushButton::loadPixmap(QString pic_name)
{
	pixmap = QPixmap(pic_name);

	btn_width = pixmap.width() / 3;
	btn_height = pixmap.height();

	this->setFixedSize(btn_width, btn_height);
}

void PushButton::enterEvent(QEvent *)
{
	status = ENTER;
	update();
}

void PushButton::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		mouse_press = true;
		status = PRESS;

		update();
	}
}

void PushButton::mouseReleaseEvent(QMouseEvent *event)
{
	if (mouse_press  && this->rect().contains(event->pos())) {
		mouse_press = false;
		status = ENTER;

		update();
		emit clicked();
	}
}

void PushButton::leaveEvent(QEvent *)
{
	status = NORMAL;
	update();
}

void PushButton::paintEvent(QPaintEvent *)
{
	QPainter painter;
	painter.begin(this);
	painter.drawPixmap(this->rect(), pixmap.copy(btn_width * status, 0, btn_width, btn_height));
	painter.end();
}
