#include "Tu_navigationbar.h"
#include "../Tu-ui/Tu-common/Tu_styleddelegate.h"

NavigationBar::NavigationBar(QWidget *parent)
    : QListWidget(parent)
{
    setFixedWidth(150);
    setFocusPolicy(Qt::NoFocus);
    setViewMode(QListView::ListMode);
    setMovement(QListView::Static);

    initUi();
}

NavigationBar::~NavigationBar()
{

}

void NavigationBar::initUi()
{
    setItemDelegate(new StyledDelegate(this));
    setObjectName("infoList");
 
    type_list << tr("Common") << tr("Document") << tr("Internet") << tr("System") << tr("Software") << tr("Other");
    for (int i = 0; i < type_list.size(); i++) {
        QListWidgetItem *item = new QListWidgetItem(type_list.at(i), this);
        item->setSizeHint(QSize(150, 67));
        item->setStatusTip(type_list.at(i));
    }

    setCurrentRow(0);
}
