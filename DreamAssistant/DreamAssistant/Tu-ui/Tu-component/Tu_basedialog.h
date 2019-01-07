#ifndef TU_BASEDIALOG_H
#define TU_BASEDIALOG_H

#include <QDialog>

class BaseDialog : public QDialog
{
	Q_OBJECT
public:
	explicit BaseDialog(QWidget *parent = Q_NULLPTR);
	~BaseDialog();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	QPoint drag_pos;
	bool mouse_press;
};

#endif // TU_BASEDIALOG_H
