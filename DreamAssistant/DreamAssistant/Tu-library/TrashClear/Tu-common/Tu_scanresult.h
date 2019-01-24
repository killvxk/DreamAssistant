#ifndef TU_SCANRESULT_H
#define TU_SCANRESULT_H

#include <QObject>
#include <QMap>
#include "../Tu-core/Tu_singleton.h"

class ScanResult
{
	SINGLETON(ScanResult)
public:
	void saveScanResult(QStringList, QString, QString, quint64);

	QStringList getCleanItem(int id);
	quint64 getSizeMap(int id);

protected:
	void insertSizeMap(int id, quint64 ssize);
	void insertCleanItem(int id, QStringList itemlist);

private:
	QMap<int, QStringList>  m_cleanMap; 
	QMap<int, quint64>      m_sizeMap; 

	quint64  m_sacnTotal; 
};

#endif // TU_SCANRESULT_H
