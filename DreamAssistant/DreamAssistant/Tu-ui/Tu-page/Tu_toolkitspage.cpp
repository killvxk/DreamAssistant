#include "Tu_toolkitspage.h"
#include <QHBoxLayout>

ToolKitsPage::ToolKitsPage(QWidget *parent, QString path)
	: QWidget(parent)
    , plugin_path(path)
{
	setFixedSize(900, 403);
	setStyleSheet("QWidget{border: none;}");
	setAutoFillBackground(true);

	initUi();
	initLayout();
}

ToolKitsPage::~ToolKitsPage()
{

}

void ToolKitsPage::initUi()
{
	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(Qt::white));
	setPalette(palette);

    navigation_bar = new NavigationBar;
    scroll_area = new ScrollArea(plugin_path);

    connect(navigation_bar, &NavigationBar::itemClicked, scroll_area, &ScrollArea::itemChanged);
}

void ToolKitsPage::initLayout()
{
    QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(navigation_bar);
    layout->addWidget(scroll_area);
	layout->setSpacing(0);
	layout->setMargin(0);
	layout->setContentsMargins(0, 0, 0, 0);

	setLayout(layout);
}
