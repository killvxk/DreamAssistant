#ifndef TU_TOOLKITSPAGE_H
#define TU_TOOLKITSPAGE_H

#include <QListView>

#include "../Tu-common/Tu_listmodel.h"

class ToolKitsPage : public QWidget
{
	Q_OBJECT
public:
	explicit ToolKitsPage(QWidget *parent = Q_NULLPTR, QString path = "");
	~ToolKitsPage();

signals:
	void sig_sendSubIndex(int index);

public slots:
	void OnClickListView(const QModelIndex & index);

protected:
	void initUi();
	void initLayout();

	void loadPlugins();
	void initPluginWidget();

private:
	QListView *list_view;
	ListModel pluginModel;

	QString plugin_path;
};

#endif // TU_TOOLKITSPAGE_H
