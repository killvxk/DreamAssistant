#include "Tu_pluginmanager.h"
#include "./Tu_plugininterface.h"
#include <QDir>

PluginManager::PluginManager()
{

}

PluginManager::~PluginManager()
{

}

PluginManager* PluginManager::Instance()
{
	static PluginManager PluginMgr;
	return &PluginMgr;
}

bool PluginManager::loadPlugin(QString plugin_path)
{
	QDir pluginsDir(plugin_path);
	foreach(QString fileName, pluginsDir.entryList(QStringList("*.dll"), QDir::Files))
	{
		QPluginLoader *pluginLoader = new QPluginLoader(pluginsDir.absoluteFilePath(fileName));
		QObject *plugin = pluginLoader->instance();

		if (plugin) {
			PluginInterface* interface = qobject_cast<PluginInterface*>(plugin);
			if (interface) {
				QString guid = interface->getGuid();
				plugin_map.insert(guid, pluginLoader);
			}
		} else {
			delete pluginLoader;
		}
	}
	return true;
}

bool PluginManager::unloadPlugin(QString plugin_guid)
{
	QMap<QString, QPluginLoader*>::iterator iter = plugin_map.find(plugin_guid);

	if (iter == plugin_map.end()) {
		return false;
	}

	iter.value()->unload();
	plugin_map.erase(iter);

	return true;
}
