#ifndef TU_SHREDFILE_H
#define TU_SHREDFILE_H

#include "../Tu-ui/Tu_shreddialog.h"
#include "Tu_plugininterface.h"

class ShredFile : public QObject, PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.dream.Plugin.ShredManager" FILE "shredfile.json")
    Q_INTERFACES(PluginInterface)
public:
    ShredFile(QObject* parent = Q_NULLPTR);
    virtual~ShredFile();

public:
    virtual QString getGuid();
    virtual QString getName();
    virtual QString getDescribe();
    virtual QString getPicture();

    virtual void doAction();

private:
    ShredDialog shred_dialog;
};

#endif // TU_SHREDFILE_H
