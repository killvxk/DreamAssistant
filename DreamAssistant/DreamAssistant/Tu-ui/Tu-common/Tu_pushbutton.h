#ifndef TU_PUSHBUTTON_H
#define TU_PUSHBUTTON_H

#include <QPushButton>

class PushButton : public QPushButton
{
	Q_OBJECT
public:
	explicit PushButton(QWidget *parent = Q_NULLPTR);
	~PushButton();

	void loadPixmap(QString pic_name);

protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	QPixmap pixmap;

	enum ButtonStatus{ NORMAL, ENTER, PRESS };
	ButtonStatus status;

	bool mouse_press; 
	int  btn_width;
	int  btn_height;
};

#endif // TU_PUSHBUTTON_H
