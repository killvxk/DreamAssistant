#ifndef TU_TOOLKITSPAGE_H
#define TU_TOOLKITSPAGE_H

#include "Tu-toolkits/Tu_navigationbar.h"
#include "Tu-toolkits/Tu_scrollarea.h"

class ToolKitsPage : public QWidget
{
	Q_OBJECT
public:
	explicit ToolKitsPage(QWidget *parent = Q_NULLPTR, QString path = "");
	~ToolKitsPage();

signals:
	void sig_sendSubIndex(int index);

protected:
	void initUi();
	void initLayout();

private:
    QString plugin_path;

    NavigationBar *navigation_bar;
    ScrollArea    *scroll_area;
};

#endif // TU_TOOLKITSPAGE_H
