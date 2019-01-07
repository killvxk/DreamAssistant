#include "Tu_basedialog.h"
#include <QMouseEvent>
#include <QCoreApplication>

BaseDialog::BaseDialog(QWidget *parent)
	: QDialog(parent)
{
	mouse_press = false;
    setWindowOpacity(1);
}

BaseDialog::~BaseDialog()
{

}



void BaseDialog::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
		mouse_press = true;

	drag_pos = event->globalPos() - pos();
}

void BaseDialog::mouseReleaseEvent(QMouseEvent *)
{
	mouse_press = false;
	setWindowOpacity(1);
}

void BaseDialog::mouseMoveEvent(QMouseEvent *event)
{
	if (mouse_press) {
		QPoint move_pos = event->globalPos();
		move(move_pos - drag_pos);

        setWindowOpacity(0.9);
	}
}
