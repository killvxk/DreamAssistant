#include "Tu_toolbutton.h"

ToolButton::ToolButton(const QString &pic_name, const QString &text, QWidget *parent)
	: QToolButton(parent)
{
	setDown(false);
	setFocusPolicy(Qt::NoFocus);

	setText(text);
	setStyleSheet("background:transparent;border:0px;color:rgb(0, 112, 223);font-weight:bold;font-size:15px;");

	setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	setPopupMode(QToolButton::InstantPopup);

	QPixmap pixmap(pic_name);
	normal_icon = QIcon(pic_name);
	hover_icon = QIcon(pic_name + "-hover");
	press_icon = QIcon(pic_name + "-press");

	setIcon(pixmap);
	setIconSize(pixmap.size());
	setAutoRaise(true);

	mouse_over = false;
	mouse_press = false;
	pressed = false;
}

ToolButton::~ToolButton()
{

}

void ToolButton::enterEvent(QEvent *event)
{
	if (isEnabled()) {
		mouse_over = true;
		this->setMouseHover();
	}
}

void ToolButton::leaveEvent(QEvent *event)
{
	if (isEnabled()) {
		mouse_over = false;
		this->setMouseHover();
	}
}

void ToolButton::mousePressEvent(QMouseEvent *event)
{
	QToolButton::mousePressEvent(event);
}

void ToolButton::setMouseHover()
{
	if (this->mouse_over) {
		this->setIcon(QIcon(hover_icon));
	} else {
		if (pressed)
			this->setIcon(QIcon(press_icon));
		else
			this->setIcon(QIcon(normal_icon));
	}
}

void ToolButton::setMousePress(bool is_press)
{
	this->mouse_press = is_press;

	if (this->mouse_press) {
		this->setIcon(QIcon(press_icon));
		pressed = true;
	} else {
		this->setIcon(QIcon(normal_icon));
		pressed = false;
	}
}
