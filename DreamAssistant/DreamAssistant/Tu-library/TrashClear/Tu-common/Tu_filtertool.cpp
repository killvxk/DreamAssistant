#include "Tu_filtertool.h"
#include <windows.h>

FilterTool::FilterTool()
{
	m_Filterfiles << "desktop.ini" << "index.dat" << "ntuser.dat" << "outlook.pst.tmp" <<
		"computer.lnk" << "control panel.lnk" << "run.lnk" << "help.lnk";

	m_DownFilterfiles << "FP_AX_CAB_INSTALLER.exe";

	m_FilterFuncMap.insert("%windir%", &FilterTool::checkWindowsPath);
	m_FilterFuncMap.insert("%program%", &FilterTool::checkProgramPath);
	m_FilterFuncMap.insert("%downloadlist%", &FilterTool::checkDownloadProPath);
	m_FilterFuncMap.insert("%specfiles%", &FilterTool::checkSpecFile);
}

FilterTool::~FilterTool()
{

}

QString FilterTool::getFileExtend(QString filename)
{
	int pos = filename.lastIndexOf('.');
	return filename.mid(pos + 1, filename.length() - pos);
}

bool FilterTool::isFilterFile(QString filename)
{
	int count = m_Filterfiles.count();

	for (int i = 0; i < count; ++i) {
		if (m_Filterfiles.at(i) == filename) {
			return true;
		}
	}

	int extend_count = m_FilterfilesEx.count();
	QString extendname = getFileExtend(filename);
	for (int i = 0; i < extend_count; ++i) {
		if (m_FilterfilesEx.at(i) == extendname) {
			return true;
		}
	}

	return false;
}

bool FilterTool::isFilterDir(QString dirname)
{
	int count = m_FilterDir.count();
	for (int i = 0; i < count; ++i) {
		if (m_FilterDir.at(i) == dirname) {
			return true;
		}
	}

	return false;
}

bool FilterTool::findFuncMap(QString strFuncName, QString strFileName)
{
	QMap<QString, Filteroperator>::iterator iter = m_FilterFuncMap.find(strFuncName);
	if (iter == m_FilterFuncMap.end()) {
		return false;
	}

	Filteroperator soperator = iter.value();
	return (this->*soperator)(strFileName);
}

bool FilterTool::checkWindowsPath(QString strFilePath)
{
	WCHAR szPath[MAX_PATH] = { 0 };
	QString strWindir;
	if (0 != ::GetWindowsDirectory(szPath, MAX_PATH)) {
		strWindir = QString::fromStdWString(szPath);
	}

	if (strFilePath.indexOf(strWindir) != -1) {
		return true;
	}

	return false;
}

bool FilterTool::checkProgramPath(QString strFilePath)
{
	WCHAR szPath[MAX_PATH] = { 0 };
	QString strSysdriver = "";

	if (0 != ::GetSystemDirectory(szPath, MAX_PATH)) {
		QString syspath = QString::fromStdWString(szPath);
		strSysdriver += syspath[0];
		strSysdriver += syspath[1];
	}

	strSysdriver = strSysdriver + "\\program files";
	if (-1 != strFilePath.lastIndexOf(strSysdriver)) {
		return true;
	}

	return false;
}

bool FilterTool::checkSpecFile(QString strFilePath)
{
	int count = m_Filterfiles.count();
	for (int i = 0; i < count; ++i) {
		if (m_Filterfiles.at(i) == strFilePath) {
			return true;
		}
	}

	return false;
}

bool FilterTool::checkDownloadProPath(QString strFilePath)
{
	int count = m_DownFilterfiles.count();
	for (int i = 0; i < count; ++i) {
		if (m_DownFilterfiles.at(i) == strFilePath) {
			return true;
		}
	}

	return false;
}
