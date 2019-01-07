#ifndef TU_PLUGININTERFACE_H
#define TU_PLUGININTERFACE_H

#include <QtCore/QtPlugin>
#include <QString>

class PluginInterface
{
public:
	virtual ~PluginInterface() {}
	virtual QString getGuid() = 0;
	virtual QString getName() = 0;
	virtual QString getDescribe() = 0;
	virtual QString getPicture() = 0;
	virtual void doAction() = 0;
};

// Q_DECLARE_INTERFACE定义在在qobject.h中，用来告诉Qt meta-object system 这个接口名称
Q_DECLARE_INTERFACE(PluginInterface, "com.dream.Plugin.PluginInterface")

#endif // TU_PLUGININTERFACE_H
