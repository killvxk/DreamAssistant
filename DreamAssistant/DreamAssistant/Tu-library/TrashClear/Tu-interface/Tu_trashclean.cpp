#include "Tu_trashclean.h"
#include "./Tu-common/Tu_configdata.h"
#include "./Tu-common/Tu_scanresult.h"
#include "./Tu-common/Tu_filedelete.h"
#include "./Tu-common/Tu_trashdefine.h"
#include <QDir>

TrashClean::TrashClean(QObject *parent)
	: TaskBase(parent)
{

}

TrashClean::~TrashClean()
{

}

int TrashClean::run()
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

		if (info.id == WIN_HUISHOUZHAN) {

		}

		QStringList listitem = Singleton<ScanResult>::Instance().getCleanItem(info.id);
		quint64 size = Singleton<ScanResult>::Instance().getSizeMap(info.id);
		for (int i = 0; i < listitem.count(); ++i) {
			Singleton<FileDelete>::Instance().TrashFileDelete(listitem.at(i));

			if (i < listitem.count() - 1) {
				emit notifyDeleteFile(listitem.at(i), 0);
			} else {
				emit notifyDeleteFile(listitem.at(i), size);
			}			
		}

		m_mutex_rawData.lock();
		if (m_list_RawData.isEmpty() == false)
			m_list_RawData.pop_front();
		nCurrSz = m_list_RawData.size();
		m_mutex_rawData.unlock();
	}

	m_mutex_rawData.lock();
	nCurrSz = m_list_RawData.size();
	m_mutex_rawData.unlock();

	emit notifyCleanFinished(this->objectName());

	if (nCurrSz == 0) {
		return 0;
	}

	return -1;
}

bool TrashClean::cleanTrash()
{
	bool result = Singleton<ConfigData>::Instance().readOneKeyConfig();
	if (result) {
		m_list_RawData = Singleton<ConfigData>::Instance().getData();
		this->setObjectName("clean_trash");
	}

	return result;
}

