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

// Q_DECLARE_INTERFACE��������qobject.h�У���������Qt meta-object system ����ӿ�����
Q_DECLARE_INTERFACE(PluginInterface, "com.dream.Plugin.PluginInterface")

#endif // TU_PLUGININTERFACE_H
