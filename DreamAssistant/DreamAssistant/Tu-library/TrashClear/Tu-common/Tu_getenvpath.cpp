#include "Tu_getenvpath.h"
#include <Shlobj.h>
#include <QSettings>
#include <QFile>
#include "./Tu-registry/Tu_operatorregedit.h"

GetEnvPath::GetEnvPath()
{
	m_sidlEntryMap.insert("CSIDL_DESKTOP", CSIDL_DESKTOP);
	m_sidlEntryMap.insert("CSIDL_INTERNET", CSIDL_INTERNET);
	m_sidlEntryMap.insert("CSIDL_PROGRAMS", CSIDL_PROGRAMS);
	m_sidlEntryMap.insert("CSIDL_CONTROLS", CSIDL_CONTROLS);
	m_sidlEntryMap.insert("CSIDL_PRINTERS", CSIDL_PRINTERS);
	m_sidlEntryMap.insert("CSIDL_PERSONAL", CSIDL_PERSONAL);
	m_sidlEntryMap.insert("CSIDL_FAVORITES", CSIDL_FAVORITES);
	m_sidlEntryMap.insert("CSIDL_STARTUP", CSIDL_STARTUP);
	m_sidlEntryMap.insert("CSIDL_RECENT", CSIDL_RECENT);
	m_sidlEntryMap.insert("CSIDL_SENDTO", CSIDL_SENDTO);
	m_sidlEntryMap.insert("CSIDL_BITBUCKET", CSIDL_BITBUCKET);
	m_sidlEntryMap.insert("CSIDL_STARTMENU", CSIDL_STARTMENU);
	m_sidlEntryMap.insert("CSIDL_DESKTOPDIRECTORY", CSIDL_DESKTOPDIRECTORY);
	m_sidlEntryMap.insert("CSIDL_DRIVES", CSIDL_DRIVES);
	m_sidlEntryMap.insert("CSIDL_NETWORK", CSIDL_NETWORK);
	m_sidlEntryMap.insert("CSIDL_NETHOOD", CSIDL_NETHOOD);
	m_sidlEntryMap.insert("CSIDL_FONTS", CSIDL_FONTS);
	m_sidlEntryMap.insert("CSIDL_TEMPLATES", CSIDL_TEMPLATES);
	m_sidlEntryMap.insert("CSIDL_COMMON_STARTMENU", CSIDL_COMMON_STARTMENU);
	m_sidlEntryMap.insert("CSIDL_COMMON_PROGRAMS", CSIDL_COMMON_PROGRAMS);
	m_sidlEntryMap.insert("CSIDL_COMMON_STARTUP", CSIDL_COMMON_STARTUP);
	m_sidlEntryMap.insert("CSIDL_COMMON_DESKTOPDIRECTORY", CSIDL_COMMON_DESKTOPDIRECTORY);
	m_sidlEntryMap.insert("CSIDL_APPDATA", CSIDL_APPDATA);
	m_sidlEntryMap.insert("CSIDL_PRINTHOOD", CSIDL_PRINTHOOD);
	m_sidlEntryMap.insert("CSIDL_ALTSTARTUP", CSIDL_ALTSTARTUP);
	m_sidlEntryMap.insert("CSIDL_COMMON_ALTSTARTUP", CSIDL_COMMON_ALTSTARTUP);
	m_sidlEntryMap.insert("CSIDL_COMMON_FAVORITES", CSIDL_COMMON_FAVORITES);
	m_sidlEntryMap.insert("CSIDL_INTERNET_CACHE", CSIDL_INTERNET_CACHE);
	m_sidlEntryMap.insert("CSIDL_COOKIES", CSIDL_COOKIES);
	m_sidlEntryMap.insert("CSIDL_HISTORY", CSIDL_HISTORY);
	m_sidlEntryMap.insert("CSIDL_LOCAL_APPDATA", CSIDL_LOCAL_APPDATA);
	m_sidlEntryMap.insert("CSIDL_COMMON_APPDATA", CSIDL_COMMON_APPDATA);
	m_sidlEntryMap.insert("CSIDL_PROGRAM_FILES_COMMON", CSIDL_PROGRAM_FILES_COMMON);
}

GetEnvPath::~GetEnvPath()
{

}

QString GetEnvPath::converScanPath(QString dir)
{
	QString EvnPath;
	int firstpos = dir.indexOf('%');
	int second = dir.indexOf('%', firstpos + 1);

	if (-1 == firstpos || -1 == second) {
		return QString();
	}

	QString strEnvName = dir.mid(firstpos + 1, second - 1);
	EvnPath = getEnvVariable(strEnvName);
	if (EvnPath.isEmpty()) {
		EvnPath = getFolderPath(strEnvName);
	}

	QString rightstr = dir.right(dir.length() - second - 1);
	if (!rightstr.isEmpty()) {
		EvnPath = EvnPath + rightstr;
	}

	return EvnPath;
}

QString GetEnvPath::getFolderPath(QString strEnvName)
{
	QMap<QString, int>::iterator iter = m_sidlEntryMap.find(strEnvName);
	if (iter == m_sidlEntryMap.end()) {
		return QString();
	}

	int cslid = iter.value();
	WCHAR szPath[MAX_PATH] = { 0 };
	QString strResult;

	if (::SHGetSpecialFolderPath(NULL, szPath, cslid, FALSE))
		strResult = QString::fromStdWString(szPath);

	return strResult;
}

void GetEnvPath::getPrePos(QString path, int& first, int& second)
{
	first = path.indexOf('%');
	second = path.indexOf('%', first + 1);
}

QString GetEnvPath::getEnvironmentPath(QString ss)
{
	int firstpos = 0;
	int second = 0;

	getPrePos(ss, firstpos, second);

	QString sleft = ss.mid(firstpos + 1, second - 1);
	QString dright = ss.mid(second + 1, sleft.length() - second);

	TCHAR szTempBuf[MAX_PATH] = { 0 };
	DWORD dwResult = GetEnvironmentVariable(sleft.toStdWString().c_str(), szTempBuf, MAX_PATH);

	QString strEnvVariable;
	if (dwResult > 0)
		strEnvVariable = QString::fromStdWString(szTempBuf);

	return strEnvVariable + dright;
}

QString GetEnvPath::getEnvVariable(QString pszName)
{
	TCHAR szBuffer[MAX_PATH] = { 0 };
	TCHAR szLongPathBuffer[MAX_PATH] = { 0 };
	QString EvnPath = "";

	int firstpos = 0;
	int second = 0;

	if (pszName == "windir") {
		UINT uResult = GetWindowsDirectory(szBuffer, MAX_PATH);
		EvnPath = QString::fromStdWString(szBuffer);

		return EvnPath;
	} 
	else if (pszName == "archivefiles") {
		TCHAR szLongPathBuffer[MAX_PATH];
		DWORD len = sizeof(szLongPathBuffer);

		// 先读取注册表获得"windows错误报告"文件夹环境变量
		OPeratorRegedit::getRegistryValue(HKEY_LOCAL_MACHINE,
										   "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VolumeCaches\\Windows Error Reporting Archive Files",
										   "Folder", NULL, (LPBYTE)szLongPathBuffer, &len);
		EvnPath = getEnvironmentPath(QString::fromStdWString(szLongPathBuffer));

		return EvnPath;
	}
	else if (pszName == "minidump") {
		TCHAR szLongPathBuffer[MAX_PATH];
		DWORD len = sizeof(szLongPathBuffer);

		// 先读取注册表获得"mini dump"文件夹环境变量
		OPeratorRegedit::getRegistryValue(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\CrashControl",
										   "MinidumpDir", NULL, (LPBYTE)szLongPathBuffer, &len);
		EvnPath = getEnvironmentPath(QString::fromStdWString(szLongPathBuffer));

		return EvnPath;
	} 
	else if (pszName == "memdump") {
		TCHAR szLongPathBuffer[MAX_PATH];
		DWORD len = sizeof(szLongPathBuffer);

		// 先读取注册表获得"mini dump"文件夹环境变量
		OPeratorRegedit::getRegistryValue(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\CrashControl",
										   "DumpFile", NULL, (LPBYTE)szLongPathBuffer, &len );
		EvnPath = getEnvironmentPath(QString::fromStdWString(szLongPathBuffer));

		return EvnPath;
	}
	else if (pszName == "xunleikankan") {
		TCHAR szLongPathBuffer[MAX_PATH];
		DWORD len = sizeof(szLongPathBuffer);

		OPeratorRegedit::getRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Thunder network\\Xmp",
										   "storepath", NULL, (LPBYTE)szLongPathBuffer, &len);
		EvnPath = getEnvironmentPath(QString::fromStdWString(szLongPathBuffer));

		return EvnPath;
	} 
	else if (pszName == "youku") {
		TCHAR szLongPathBuffer[MAX_PATH];
		DWORD len = sizeof(szLongPathBuffer);

		OPeratorRegedit::getRegistryValue(HKEY_CURRENT_USER, "SOFTWARE\\youku\\iKuAcc",
										   "CachePath", NULL, (LPBYTE)szLongPathBuffer, &len);
		EvnPath = getEnvironmentPath(QString::fromStdWString(szLongPathBuffer));

		return EvnPath;
	} 
	else if (pszName == "qqlive") {
		QString strTmp = getFolderPath("CSIDL_APPDATA");
		strTmp += "\\Tencent\\QQLive\\user.ini";

		// 读取配置文件里的缓存路径
		if (!QFile::exists(strTmp)) {
			return QString();
		}

		QSettings iniread(strTmp, QSettings::IniFormat, 0);
		EvnPath = iniread.value("Cache/Directory").toString();
	} 
	else if (pszName == "pptv") {
		QString strTmp = getFolderPath("CSIDL_COMMON_APPDATA");
		strTmp += "\\PPLive\\Core\\config.ini";
		if (!QFile::exists(strTmp)) {
			return QString();
		}

		QSettings iniread(strTmp, QSettings::IniFormat, 0);
		EvnPath = iniread.value("peer/cachepath").toString();
	}

	// 通过环境变量名称查找路径
	if (!pszName.isEmpty()) {
		TCHAR szTempBuf[MAX_PATH] = { 0 };
		DWORD dwResult = GetEnvironmentVariable(pszName.toStdWString().c_str(), szTempBuf, MAX_PATH);
		if (dwResult > 0)
			EvnPath = QString::fromStdWString(szTempBuf);
	}

	return EvnPath;
}
