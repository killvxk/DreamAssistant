#ifndef TU_CONFIGDATA_H
#define TU_CONFIGDATA_H

#include <QString>
#include <QList>
#include "Tu_scandirinfo.h"
#include "../Tu-core/Tu_singleton.h"

class ConfigData
{
	SINGLETON(ConfigData)
public:
	const QList<ScanDirInfo>& getData() { return m_configData; }
	int count() { return m_configData.count(); }

	ScanDirInfo getItem(QString friendName);

	bool readOneKeyConfig();

protected:
	bool convToLocatePath();

private:
	QList<ScanDirInfo> m_configData;
};

#endif // TU_CONFIGDATA_H
