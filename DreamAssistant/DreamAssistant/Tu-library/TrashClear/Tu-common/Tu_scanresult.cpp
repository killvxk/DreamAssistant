#include "Tu_scanresult.h"
#include "Tu_configdata.h"
#include "Tu_filtertool.h"
#include <QDir>

ScanResult::ScanResult()
{
	m_sacnTotal = 0;
}

ScanResult::~ScanResult()
{

}

void ScanResult::insertSizeMap(int id, quint64 size)
{
	QMap<int, quint64>::iterator iter = m_sizeMap.find(id);

	if (iter == m_sizeMap.end()) {
		m_sizeMap.insert(id, size);
	} else {
		iter.value() += size;
	}
}

void ScanResult::insertCleanItem(int id, QStringList itemlist)
{
	QMap<int, QStringList>::iterator iter = m_cleanMap.find(id);

	if (iter == m_cleanMap.end()) {
		m_cleanMap.insert(id, itemlist);
	} else {
		iter.value() << itemlist;
	}
}

quint64 ScanResult::getSizeMap(int id)
{
	QMap<int, quint64>::iterator iter = m_sizeMap.find(id);
	if (iter != m_sizeMap.end()) {
		return iter.value();
	}

	return 0;
}

QStringList ScanResult::getCleanItem(int id)
{
	QMap<int, QStringList>::iterator iter = m_cleanMap.find(id);
	if (iter == m_cleanMap.end()) {
		return QStringList();
	}

	return iter.value();
}

void ScanResult::saveScanResult(QStringList afterfiles, QString path, QString friendName, quint64 size)
{
	m_sacnTotal += size;

	const ScanDirInfo &info = Singleton<ConfigData>::Instance().getItem(friendName);

	insertSizeMap(info.id, size);

	QStringList clearlist;
	for (int i = 0; i < afterfiles.count(); ++i) {
		QString dir = afterfiles.at(i);
		if (Singleton<FilterTool>::Instance().isFilterFile(dir))
			continue;

		QString absoltpath = path + "/" + dir;   
		clearlist.append(QDir::toNativeSeparators(absoltpath));
	}

	if (!clearlist.isEmpty()) {
		insertCleanItem(info.id, clearlist);
	}
}
