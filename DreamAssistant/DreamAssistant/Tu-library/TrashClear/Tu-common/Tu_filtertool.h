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

	//查找过滤
	bool findFuncMap(QString strFuncName, QString strFileName);

public:
	bool checkWindowsPath(QString strFilePath);
	bool checkProgramPath(QString strFilePath);
	bool checkDownloadProPath(QString strFilePath);
	bool checkSpecFile(QString strFile);

private:
	QStringList m_Filterfiles;       // 指定需要过滤的文件
	QStringList m_FilterDir;         // 需要过滤的目录
	QStringList m_FilterfilesEx;     // 需要过来的扩展名
	QStringList m_DownFilterfiles;   // 下载目录过滤文件 

	QMap<QString, Filteroperator> m_FilterFuncMap;   //函数映射表
};

#endif // TU_FILTERTOOL_H
