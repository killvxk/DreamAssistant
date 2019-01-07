#ifndef TU_ACTIONWIDGET_H
#define TU_ACTIONWIDGET_H

#include <QWidget>

class ActionWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ActionWidget(QWidget *parent = Q_NULLPTR);
	~ActionWidget();
};

#endif // TU_ACTIONWIDGET_H
