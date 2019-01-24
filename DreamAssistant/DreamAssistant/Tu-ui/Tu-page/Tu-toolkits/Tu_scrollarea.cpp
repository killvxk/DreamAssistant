#include "Tu_scrollarea.h"
#include <QFile>
#include <QDomDocument>
#include <QScrollBar>
#include <QVBoxLayout>

#include "../Tu-plugins/Tu_plugininterface.h"
#include "../Tu-plugins/Tu_pluginmanager.h"

ScrollItem::ScrollItem(QString title, QString path, QWidget *parent)
    : QWidget(parent)
    , plugin_path(path)
{
    loadPlugins();
    initPlugins();

    title_label = new QLabel(title);
    title_label->setStyleSheet("color:#666;font-family: 方正黑体_GBK;font-size: 13px;font-weight:bold;");

    list_view = new QListView(this);
    list_view->setFocusPolicy(Qt::NoFocus);
    list_view->setAutoFillBackground(true);
    list_view->setIconSize(QSize(48, 48));
    list_view->setResizeMode(QListView::Adjust);
    list_view->setModel(&pluginModel);
    list_view->setViewMode(QListView::IconMode);
    list_view->setSpacing(26);
    list_view->setStyleSheet("color:#666;font-family: 方正黑体_GBK;font-size: 13px;");
    connect(list_view, &QListView::clicked, this, &ScrollItem::onClickListView);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(title_label);
    layout->addWidget(list_view);
    layout->setSpacing(0);
    layout->setContentsMargins(40, 25, 40, 25);
    setLayout(layout);
}

ScrollItem::~ScrollItem()
{

}

void ScrollItem::loadPlugins()
{
    PluginManager::Instance()->loadPlugin(plugin_path);
}

void ScrollItem::initPlugins()
{
    QStringList title;
    title << tr("");

    pluginModel.setTitle(title);
    pluginModel.insertRows(0, 1, QModelIndex());
    QModelIndex qindex = pluginModel.index(0, 0, QModelIndex());
    //set text
    pluginModel.setData(qindex, tr("Shred File"));
    //set icon
    pluginModel.setData(qindex, QIcon(QPixmap(":/res/plugins/shred/shredder.png")), Qt::DecorationRole);
    //set tooltip
    pluginModel.setData(qindex, tr("Shred File"), Qt::WhatsThisRole);

    int count = PluginManager::Instance()->count();
    for (int i = 0; i < count; ++i) {
        PluginInterface* ICommon = PluginManager::Instance()->getInterfaceByindex<PluginInterface>(i);
        QString picture = ICommon->getPicture();
        QString  pacture_path = QString(":/model/res/plugin/%1").arg(picture);
        pluginModel.setGuid(ICommon->getGuid());
        pluginModel.insertRows(i + 3, 1, QModelIndex());
        // 		qindex = pluginModel.index(i + 3, 0, QModelIndex());
        // 		pluginModel.setData(qindex, ICommon->getName());
        // 		pluginModel.setData(qindex, QIcon(QPixmap(pacture_path)), Qt::DecorationRole);
        // 		pluginModel.setData(qindex, ICommon->getName(), Qt::WhatsThisRole);
    }
}

void ScrollItem::onClickListView(const QModelIndex &index)
{
    QString guid = pluginModel.getGuid(index.row());
    PluginInterface* interface = PluginManager::Instance()->getInterfaceByGuid<PluginInterface>(guid);
    interface->doAction(); 
}


ScrollArea::ScrollArea(QString path, QWidget *parent)
    : QScrollArea(parent)
    , plugin_path(path)
{
    setStyleSheet("background:transparent;");
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    readData(path + "/plugins");

    initUi();
}

ScrollArea::~ScrollArea()
{
    for (std::vector<TreeNode *>::iterator it = treeNode.begin(); it != treeNode.end();) {
        for (std::list<TreeNode *>::iterator child = (*it)->children.begin(); child != (*it)->children.end();) {
            delete(*child);
            child = (*it)->children.erase(child);
        }

        delete(*it);
        it = treeNode.erase(it);
    }
}

void ScrollArea::initUi()
{
    content_widget = new QWidget;
    content_widget->resize(750, 1500);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(new ScrollItem(tr("Common"), plugin_path + "/plugins/common"));
    layout->addWidget(new ScrollItem(tr("Document"), plugin_path + "/plugins/common"));
    layout->addWidget(new ScrollItem(tr("Internet"), plugin_path + "/plugins/common"));
    layout->addWidget(new ScrollItem(tr("System"), plugin_path + "/plugins/common"));
    layout->addWidget(new ScrollItem(tr("Software"), plugin_path + "/plugins/common"));
    layout->addWidget(new ScrollItem(tr("Others"), plugin_path + "/plugins/common"));
    layout->addStretch();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    content_widget->setLayout(layout);

    setWidget(content_widget);
}

void ScrollArea::initLayout()
{

}

void ScrollArea::initConnect()
{

}

void ScrollArea::readData(QString path)
{
    QFile xml(path);

    if (!xml.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&xml, false)) {
        return;
    }

    treeNode.clear();

    QDomNode root = doc.documentElement().firstChildElement("layout");
    QDomNodeList children = root.childNodes();

    for (int i = 0; i != children.count(); ++i) {
        QDomElement nodeInfo = children.at(i).toElement();
        TreeNode *node = new TreeNode;
        node->icon = nodeInfo.attribute("icon");
        node->label = nodeInfo.attribute("label");
        node->collapse = nodeInfo.attribute("collapse").toInt();
        node->info = nodeInfo.attribute("info");
        node->level = 1;

        QDomNodeList secondLevel = nodeInfo.childNodes();

        for (int j = 0; j != secondLevel.count(); ++j) {
            QDomElement secNodeInfo = secondLevel.at(j).toElement();
            TreeNode *secNode = new TreeNode;
            secNode->icon = secNodeInfo.attribute("icon");
            secNode->label = secNodeInfo.attribute("label");
            secNode->info = secNodeInfo.attribute("info");
            secNode->collapse = false;
            secNode->level = 2;
            secNode->theLast = (j == secondLevel.count() - 1 && i != children.count() - 1);
            node->children.push_back(secNode);
        }

        treeNode.push_back(node);
    }
}

void ScrollArea::refreshList()
{
    listNode.clear();

    for (std::vector<TreeNode *>::iterator it = treeNode.begin(); it != treeNode.end(); ++it) {
        ListNode node;
        node.label = (*it)->label;
        node.treeNode = *it;

        listNode.push_back(node);

        if ((*it)->collapse) {
            continue;
        }

        for (std::list<TreeNode *>::iterator child = (*it)->children.begin(); child != (*it)->children.end(); ++child) {
            ListNode node;
            node.label = (*child)->label;
            node.treeNode = *child;
            node.treeNode->theLast = false;
            listNode.push_back(node);
        }

        if (!listNode.empty()) {
            listNode.back().treeNode->theLast = true;
        }
    }
}

void ScrollArea::itemChanged(QListWidgetItem *item)
{
    if (status_tip == item->statusTip()) {
        return;
    }

    status_tip = item->statusTip();

    foreach (QObject *obj, content_widget->children()) {
        if (obj->metaObject()->className() != QString("ScrollItem")) {
            continue;
        }

        ScrollItem *item = static_cast<ScrollItem *>(obj);
        if (item->title() == status_tip) {
            this->verticalScrollBar()->setValue(item->y());
            return;
        }
    }
}
