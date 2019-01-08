#ifndef TU_TITLEBAR_H
#define TU_TITLEBAR_H

#include <QWidget>
#include <QLabel>

#include "../Tu-common/Tu_pushbutton.h"

class TitleBar : public QWidget
{
	Q_OBJECT
public:
	explicit TitleBar(QWidget *parent = Q_NULLPTR);
	~TitleBar();

	void setTitleWidth(int width) { title_width = width; }
	void setTitleName(QString title) { title_content = title; }
	void setTitleBackgound(QString img) { backgroud_image = img; }

	void resetBackground(QString name);

protected:
	virtual void resizeEvent(QResizeEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

signals:
	void sig_closeDialog();

private:
	QPoint  press_point;
	QPoint  move_point;
	bool left_btn_pressed;

	QLabel *title_label;
	int title_width;

	QString title_content;
	QString backgroud_image;

	PushButton *close_btn;
};

#endif // TU_TITLEBAR_H
