#include "Tu_trashscan.h"
#include "./Tu-common/Tu_trashdefine.h"
#include "./Tu-common/Tu_filtertool.h"
#include "./Tu-common/Tu_configdata.h"
#include "./Tu-common/Tu_scanresult.h"
#include <Shlwapi.h>
#include <QDir>

TrashScan::TrashScan(QObject *parent)
	: TaskBase(parent)
{
	
}

TrashScan::~TrashScan()
{
	
}

int TrashScan::run()
{
	int nCurrSz = -1;
	while (nCurrSz != 0)
	{
        if (bTermSet == true)
            return 0;

		ScanDirInfo info;
		m_mutex_rawData.lock();
		if (m_list_RawData.size())
			info = *m_list_RawData.begin();
		m_mutex_rawData.unlock();

		bool result = findFileInDirectory(info);
		if (result) {
			m_mutex_rawData.lock();
			if (m_list_RawData.isEmpty() == false)
				m_list_RawData.pop_front();
			m_mutex_rawData.unlock();
		}

		m_mutex_rawData.lock();
		nCurrSz = m_list_RawData.size();
		m_mutex_rawData.unlock();
	}

	m_mutex_rawData.lock();
	nCurrSz = m_list_RawData.size();
	m_mutex_rawData.unlock();

	emit notifyScanFinished(this->objectName());

	if (nCurrSz == 0) {
		return 0;
	}

	return -1;
}

bool TrashScan::oneKeyScan()
{
	bool result = Singleton<ConfigData>::Instance().readOneKeyConfig();
	if (result) {
		m_list_RawData = Singleton<ConfigData>::Instance().getData();
		this->setObjectName("onekey_scan_trash");
	}
	
	return result;
}

bool TrashScan::findFileInDirectory(const ScanDirInfo& info)
{
	if (info.id == WIN_HUISHOUZHAN) {
		SHQUERYRBINFO syscleInfo = { 0 };
		syscleInfo.cbSize = sizeof(SHQUERYRBINFO);
		int iCount = SHQueryRecycleBin(NULL, &syscleInfo);

		if (syscleInfo.i64NumItems > 0) {
			emit notifyRecycleBin((quint32)syscleInfo.i64NumItems, (quint64)syscleInfo.i64Size / 1024);
		}

		return true;
	}

	int count = info.strDirectory.count();
	for (int i = 0; i < count; ++i) {
		// 处理掉不存在，或者不合法的目录
		QString finddir = info.strDirectory.at(i);
		QDir dir(finddir);
		if (!dir.exists()) {
			continue;
		}

        if (bTermSet == true)
            return 0;

		emit notifyCurrentScanDir(finddir);
		findFileWithExtInDirectory(finddir, info.strExtArray, info.strFilt, info.id, info.strFriendName);

		// 如果设置为递归搜索文件夹
		if (info.bRecursive) {
			QStringList subdir = getSubDir(finddir);
			for (int j = 0; j < subdir.count(); ++j) {
				ScanDirInfo subinfo = info;
				subinfo.strDirectory.clear();
				subinfo.strDirectory << subdir.at(j);

				findFileInDirectory(subinfo);
			}
		}
	}

	return true;
}

bool TrashScan::findFileWithExtInDirectory(QString path, QStringList strExtArray, QStringList strFilt, int index, QString FriendName)
{
	QDir dir(path);
	QStringList entryfiles;
	QStringList afterfiles;

	if (strExtArray.at(0) == "*.*") {
		entryfiles = dir.entryList(QDir::Files | QDir::Hidden | QDir::System);
	} else {
		entryfiles = dir.entryList(strExtArray, QDir::Files | QDir::Hidden | QDir::System);
	}

	if (!entryfiles.isEmpty()) {
		// 过滤文件
		for (int i = 0; i < entryfiles.count(); ++i) {
            if (bTermSet == true)
                return 0;

			bool isfilter = false;
			for (int index = 0; index < strFilt.count(); ++index) {
				if (Singleton<FilterTool>::Instance().findFuncMap(strFilt.at(index), entryfiles.at(i))) {
					isfilter = true;
					break;
				}
			}

			if (!isfilter) {
				afterfiles.append(entryfiles.at(i));

				if (afterfiles.size() > 500) {
					quint64 size = calculatedSize(path, afterfiles);
					emit notifyScanDirItem(afterfiles, path, FriendName, size);
					Singleton<ScanResult>::Instance().saveScanResult(afterfiles, path, FriendName, size);

					afterfiles.clear();
				}
			}
		}
		quint64 size = calculatedSize(path, afterfiles);  
		emit notifyScanDirItem(afterfiles, path, FriendName, size);
		Singleton<ScanResult>::Instance().saveScanResult(afterfiles, path, FriendName, size);
	}

	return true;
}

QStringList TrashScan::getSubDir(QString path)
{
	QDir dir(path);
	QStringList entryDir;
	QStringList absoluteDir;
	entryDir = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);

	for (int i = 0; i < entryDir.count(); ++i) {
		QString absolutePath = path + "\\" + entryDir.at(i);
		absoluteDir.append(absolutePath);
	}

	return absoluteDir;
}

quint64 TrashScan::calculatedSize(QString path, QStringList fiels)
{
	int count = fiels.count();
	int clusterSize = 4096;

	quint64 tatol = 0;
	DWORD filesize;

	for (int i = 0; i < count; ++i) {
		if (Singleton<FilterTool>::Instance().isFilterFile(fiels.at(i))) {
			continue;
		}

		QString filepath = path + "/" + fiels.at(i);
		QString nativpath = QDir::toNativeSeparators(filepath);
		QFileInfo fileinfo(nativpath);

		if ((fileinfo.size() % clusterSize) == 0) {
			tatol += fileinfo.size();
		} else {
			double res = fileinfo.size() / clusterSize;
			int clu = ceil(res) + 1;
			float temp = clusterSize * clu;
			tatol += temp;
		}
	}

	return static_cast<quint64>(tatol / 1024);
}
