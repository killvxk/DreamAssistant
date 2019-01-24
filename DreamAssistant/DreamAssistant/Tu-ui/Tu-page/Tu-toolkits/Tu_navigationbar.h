#ifndef TU_NAVIGATIONBAR_H
#define TU_NAVIGATIONBAR_H

#include <QListWidget>

class NavigationBar : public QListWidget
{
    Q_OBJECT
public:
    explicit NavigationBar(QWidget *parent = Q_NULLPTR);
    ~NavigationBar();

protected:
    void initUi();

private:
    QStringList type_list;
};

#endif // TU_NAVIGATIONBAR_H
