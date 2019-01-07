#ifndef TU_TOOLWIDGET_H
#define TU_TOOLWIDGET_H

#include <QWidget>

#include "../Tu-common/Tu_toolbutton.h"

class ToolWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ToolWidget(QWidget *parent = Q_NULLPTR);
	~ToolWidget();

signals:
	void sig_turnCurrentPage(int index);

public slots:
	void switchSelectedPageIndex(QString index);
	void showBoxTool();

protected:
	void initConnect();

private:
	QList<ToolButton *> button_list;
};

#endif // TU_TOOLWIDGET_H
