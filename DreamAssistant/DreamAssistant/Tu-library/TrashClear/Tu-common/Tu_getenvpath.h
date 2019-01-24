#ifndef TU_GETENVPATH_H
#define TU_GETENVPATH_H

#include <QMap>
#include "../Tu-core/Tu_singleton.h"

class GetEnvPath
{
	SINGLETON(GetEnvPath)
public:
	QString converScanPath(QString dir);

protected:
	QString getEnvVariable(QString pszName);
	QString getFolderPath(QString strEnvName);
	QString getEnvironmentPath(QString ss);

	void getPrePos(QString path, int& first, int& second);

private:
	QMap<QString, int> m_sidlEntryMap;
};

#endif // TU_GETENVPATH_H
