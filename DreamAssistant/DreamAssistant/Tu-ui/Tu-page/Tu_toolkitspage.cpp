#include "Tu_toolkitspage.h"
#include <QGridLayout>

#include "Tu-toolkits/Tu_plugininterface.h"
#include "Tu-toolkits/Tu_pluginmanager.h"

ToolKitsPage::ToolKitsPage(QWidget *parent, QString path)
	: QWidget(parent), plugin_path(path)
{
	setFixedSize(900, 403);
	setStyleSheet("QWidget{border: none;}");
	setAutoFillBackground(true);

	initUi();
	initLayout();
	
	loadPlugins();
	initPluginWidget();
	connect(list_view, SIGNAL(clicked(const QModelIndex&)), this, SLOT(OnClickListView(const QModelIndex &)));
}

ToolKitsPage::~ToolKitsPage()
{

}

void ToolKitsPage::initUi()
{
	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(Qt::white));
	setPalette(palette);

	list_view = new QListView(this);
	list_view->setFocusPolicy(Qt::NoFocus);
	list_view->setAutoFillBackground(true);
	list_view->setIconSize(QSize(48, 48));
	list_view->setResizeMode(QListView::Adjust);
	list_view->setModel(&pluginModel);
	list_view->setViewMode(QListView::IconMode);
	list_view->setSpacing(26);
}

void ToolKitsPage::initLayout()
{
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(list_view);
	layout->setSpacing(0);
	layout->setMargin(0);
	layout->setContentsMargins(0, 0, 0, 0);
	setLayout(layout);
}

void ToolKitsPage::loadPlugins()
{
	PluginManager::Instance()->loadPlugin(plugin_path);
}

void ToolKitsPage::initPluginWidget()
{
	QStringList title;
	title << tr("");

	pluginModel.setTitle(title);
	pluginModel.insertRows(0, 1, QModelIndex());
	QModelIndex qindex = pluginModel.index(0, 0, QModelIndex());
	//set text
	pluginModel.setData(qindex, tr("Shred File"));
	//set icon
	pluginModel.setData(qindex, QIcon(QPixmap("")), Qt::DecorationRole);
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

void ToolKitsPage::OnClickListView(const QModelIndex & index)
{
	QString guid = pluginModel.getGuid(index.row());
	PluginInterface* interface = PluginManager::Instance()->getInterfaceByGuid<PluginInterface>(guid);
	interface->doAction();
}
