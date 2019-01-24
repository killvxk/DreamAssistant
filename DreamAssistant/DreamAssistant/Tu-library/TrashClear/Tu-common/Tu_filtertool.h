#ifndef TU_FILTERTOOL_H
#define TU_FILTERTOOL_H

#include <QStringList>
#include <QMap>
#include "../Tu-core/Tu_singleton.h"

class FilterTool
{
	SINGLETON(FilterTool)
public:
	bool isFilterFile(QString filename);
	bool isFilterDir(QString dirname);
	QString getFileExtend(QString filename);

	typedef bool (FilterTool::*Filteroperator)(QString file);

	//���ҹ���
	bool findFuncMap(QString strFuncName, QString strFileName);

public:
	bool checkWindowsPath(QString strFilePath);
	bool checkProgramPath(QString strFilePath);
	bool checkDownloadProPath(QString strFilePath);
	bool checkSpecFile(QString strFile);

private:
	QStringList m_Filterfiles;       // ָ����Ҫ���˵��ļ�
	QStringList m_FilterDir;         // ��Ҫ���˵�Ŀ¼
	QStringList m_FilterfilesEx;     // ��Ҫ��������չ��
	QStringList m_DownFilterfiles;   // ����Ŀ¼�����ļ� 

	QMap<QString, Filteroperator> m_FilterFuncMap;   //����ӳ���
};

#endif // TU_FILTERTOOL_H
