#ifndef TU_CONTENTWIDGET_H
#define TU_CONTENTWIDGET_H

#include <QWidget>

class ContentWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ContentWidget(QWidget *parent = Q_NULLPTR);
	~ContentWidget();
};

#endif // TU_CONTENTWIDGET_H
