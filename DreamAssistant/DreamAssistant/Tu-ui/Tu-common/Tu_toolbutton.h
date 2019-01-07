#ifndef TU_TOOLBUTTON_H
#define TU_TOOLBUTTON_H

#include <QToolButton>

class ToolButton : public QToolButton
{
	Q_OBJECT
public:
	explicit ToolButton(const QString &pic_name, const QString &text, QWidget *parent = Q_NULLPTR);
	~ToolButton();

	void setMousePress(bool is_press);
	void setMouseHover();

	bool pressed;

protected:
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
	void mousePressEvent(QMouseEvent *event);

public:
	bool mouse_over;  // 鼠标是否移过
	bool mouse_press; // 鼠标是否按下

	QIcon normal_icon;
	QIcon hover_icon;
	QIcon press_icon;
};

#endif // TU_TOOLBUTTON_H
