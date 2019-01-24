#ifndef TU_SCROLLAREA_H
#define TU_SCROLLAREA_H

#include <QScrollArea>
#include <QListView>
#include <QLabel>
#include <QListWidgetItem>

#include "../Tu-ui/Tu-common/Tu_listmodel.h"

class ScrollItem : public QWidget
{
    Q_OBJECT

public:
    explicit ScrollItem(QString title, QString path, QWidget *parent = Q_NULLPTR);
    ~ScrollItem();

    QString title() const { return title_label->text(); }

public slots:
    void onClickListView(const QModelIndex &index);

protected:
    void loadPlugins();
    void initPlugins();

private:
    QString plugin_path;

    QLabel *title_label;

    QListView *list_view;
    ListModel pluginModel;
};

class ScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit ScrollArea(QString path, QWidget *parent = Q_NULLPTR);
    ~ScrollArea();

    struct TreeNode {
        QString icon;
        QString label;
        int level;
        bool collapse;
        bool theLast;
        QString info;
        std::list<TreeNode *> children;
    };

    struct ListNode {
        QString label;
        TreeNode *treeNode;
    };

public slots:
    void itemChanged(QListWidgetItem *);

protected:
    void initUi();
    void initLayout();
    void initConnect();

    void readData(QString path);
    void refreshList();

private:
    std::vector<TreeNode *> treeNode;
    std::vector<ListNode> listNode;

    QString plugin_path;
    QString status_tip;

    QWidget *content_widget;
};

#endif // TU_SCROLLAREA_H
