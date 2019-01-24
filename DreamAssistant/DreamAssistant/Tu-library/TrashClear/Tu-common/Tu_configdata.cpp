#include "Tu_configdata.h"
#include "Tu_trashdefine.h"
#include "Tu_scandirinfo.h"
#include "Tu_getenvpath.h"

ConfigData::ConfigData()
{

}

ConfigData::~ConfigData()
{

}

bool ConfigData::convToLocatePath()
{
	if (m_configData.size() <= 0) {
		return false;
	}

	for (int i = 0; i < m_configData.count(); ++i) {
		const ScanDirInfo& info = m_configData.at(i);
		int dir_count = info.strDirectory.count();

		for (int c = 0; c < dir_count; ++c) {
			QString EvnPath = Singleton<GetEnvPath>::Instance().converScanPath(info.strDirectory.at(c));
			if (!EvnPath.isEmpty()) {
				m_configData[i].strDirectory.replace(c, EvnPath);
			}
		}
	}

	return true;
}

bool ConfigData::readOneKeyConfig()
{
	m_configData.clear();

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = false;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strFriendName = QStringLiteral("Windows系统垃圾文件");
		dirinfo.id = WIN_TRASH;
		dirinfo.parent = NONE;
		dirinfo.bIsLeaf = false;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = true;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.clear();
		dirinfo.strDirectory.push_back("");
		dirinfo.strFriendName = QStringLiteral("回收站");
		dirinfo.strExtArray.clear();
		dirinfo.strExtArray.push_back("");
		dirinfo.strFilt.clear();
		dirinfo.strFilt.push_back("");
		dirinfo.id = WIN_HUISHOUZHAN;
		dirinfo.parent = WIN_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = true;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%TEMP%");
		dirinfo.strDirectory.push_back("%usertemp%");
		dirinfo.strFriendName = QStringLiteral("用户临时文件夹");
		dirinfo.strExtArray.push_back("*");
		dirinfo.strFilt.push_back("%windir%");
		dirinfo.strFilt.push_back("%driver%");
		dirinfo.strFilt.push_back("%program%");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = WIN_USERTEMP;
		dirinfo.parent = WIN_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = true;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%windir%\\temp");
		dirinfo.strDirectory.push_back("%wintemp%");
		dirinfo.strFriendName = QStringLiteral("Windows 临时目录");
		dirinfo.strExtArray.push_back("*");
		dirinfo.strFilt.push_back("%driver%");
		dirinfo.strFilt.push_back("%program%");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = WIN_TEMP;
		dirinfo.parent = WIN_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = true;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.clear();
		dirinfo.strDirectory.push_back("%CSIDL_LOCAL_APPDATA%\\Microsoft\\Windows\\Explorer");
		dirinfo.strFriendName = QStringLiteral("缩略图缓存");
		dirinfo.strExtArray.clear();
		dirinfo.strExtArray.push_back("db");
		dirinfo.strFilt.clear();
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = WIN_SUOLIETU;
		dirinfo.parent = WIN_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = true;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.clear();
		dirinfo.strDirectory.push_back("%archivefiles%");
		dirinfo.strDirectory.push_back("%queuefiles%");
		dirinfo.strDirectory.push_back("%systemarchivefiles%");
		dirinfo.strDirectory.push_back("%systemqueuefiles%");
		dirinfo.strFriendName = QStringLiteral("Windows错误报告");
		dirinfo.strExtArray.clear();
		dirinfo.strExtArray.push_back("*");
		dirinfo.strFilt.clear();
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = WIN_ERRPORT;
		dirinfo.parent = WIN_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = true;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%windir%\\SoftwareDistribution\\Download");
		dirinfo.strFriendName = QStringLiteral("Windows 更新补丁");
		dirinfo.strExtArray.push_back("*");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = WIN_UPDATE;
		dirinfo.parent = WIN_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = true;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%windir%\\Prefetch");
		dirinfo.strFriendName = QStringLiteral("Windows 预读文件");
		dirinfo.strExtArray.push_back("pf");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = WIN_PREFETCH;
		dirinfo.parent = WIN_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%windir%\\Downloaded Program Files");
		dirinfo.strFriendName = QStringLiteral("已下载程序文件");
		dirinfo.strExtArray.push_back("*");
		dirinfo.strFilt.push_back("%downloadlist%");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = WIN_DOWNLOAD;
		dirinfo.parent = WIN_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = false;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.clear();
		dirinfo.strDirectory.push_back("%minidump%");
		dirinfo.strDirectory.push_back("%memdump%");
		dirinfo.strFriendName = QStringLiteral("内存转储文件");
		dirinfo.strExtArray.clear();
		dirinfo.strExtArray.push_back("dmp");
		dirinfo.strFilt.clear();
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = WIN_DUMP;
		dirinfo.parent = WIN_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = false;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.clear();
		dirinfo.strDirectory.push_back("%windir%\\");
		dirinfo.strDirectory.push_back("%windir%\\debug");
		dirinfo.strDirectory.push_back("%windir%\\system32\\wbem");
		dirinfo.strDirectory.push_back("%windir%\\security\\logs");
		dirinfo.strFriendName = QStringLiteral("系统日志文件");
		dirinfo.strExtArray.clear();
		dirinfo.strExtArray.push_back("log");
		dirinfo.strExtArray.push_back("lo_");
		dirinfo.strExtArray.push_back("log.txt");
		dirinfo.strExtArray.push_back("bak");
		dirinfo.strExtArray.push_back("old");
		dirinfo.strFilt.clear();
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = WIN_LOG;
		dirinfo.parent = WIN_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%CSIDL_LOCAL_APPDATA%\\Microsoft\\Terminal Server Client\\Cache");
		dirinfo.strFriendName = QStringLiteral("远程桌面");
		dirinfo.strExtArray.push_back("*");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = WIN_REMOTE_DESKTOP;
		dirinfo.parent = WIN_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%office%");
		dirinfo.strFriendName = QStringLiteral("Office 安装缓存目录");
		dirinfo.strExtArray.push_back("*");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = WIN_OFFICE;
		dirinfo.parent = COMMON_SOFTWARE;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%CSIDL_APPDATA%\\Microsoft\\MSN Messenger");
		dirinfo.strDirectory.push_back("%CSIDL_PROGRAM_FILES_COMMON%\\Windows Live\\.cache");
		dirinfo.strFriendName = "Windows Live Messenger";
		dirinfo.strExtArray.push_back("msi");
		dirinfo.strExtArray.push_back("sqm");
		dirinfo.strExtArray.push_back("ini");
		dirinfo.strExtArray.push_back("exe");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = WIN_LIVE_MGR;
		dirinfo.parent = COMMON_SOFTWARE;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.clear();
		dirinfo.strDirectory.push_back("%CSIDL_LOCAL_APPDATA%\\Google\\Picasa2\\db3");
		dirinfo.strFriendName = "picasa";
		dirinfo.strExtArray.push_back("bigthumbs_0.db");
		dirinfo.strExtArray.push_back("previews_0.db");
		dirinfo.id = SOFT_PICASA;
		dirinfo.parent = COMMON_SOFTWARE;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%systemdrive%");
		dirinfo.strFriendName = QStringLiteral("系统盘垃圾文件深度搜索");
		dirinfo.strExtArray.push_back("tmp");
		dirinfo.strExtArray.push_back("_mp");
		dirinfo.strExtArray.push_back("gid");
		dirinfo.strExtArray.push_back("chk");
		dirinfo.strExtArray.push_back("??$");
		dirinfo.strExtArray.push_back("^*");
		dirinfo.strExtArray.push_back("temp");
		dirinfo.strExtArray.push_back("~mp");
		dirinfo.strExtArray.push_back("$*");
		dirinfo.strExtArray.push_back("___");
		dirinfo.strExtArray.push_back("$$$");
		dirinfo.strExtArray.push_back("@@@");
		dirinfo.strExtArray.push_back("---");
		dirinfo.strExtArray.push_back("ftg");
		dirinfo.strExtArray.push_back("%%%");
		dirinfo.strExtArray.push_back("fts");
		dirinfo.strExtArray.push_back("prv");
		dirinfo.strExtArray.push_back("fnd");
		dirinfo.strExtArray.push_back("err");
		dirinfo.strExtArray.push_back("diz");
		dirinfo.strExtArray.push_back("mch");
		dirinfo.strExtArray.push_back("mscreate.dir");
		dirinfo.strExtArray.push_back("imagedb.aid");
		dirinfo.strExtArray.push_back("errorlog.txt");
		dirinfo.strExtArray.push_back("comsetup.txt");
		dirinfo.strExtArray.push_back("directx.txt");
		dirinfo.strExtArray.push_back("mpcsetup.txt");
		dirinfo.strExtArray.push_back("netsetup.txt");
		dirinfo.strExtArray.push_back("thumbs.db");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = SYS_TRASH;
		dirinfo.parent = NONE;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = true;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strFriendName = QStringLiteral("浏览器缓存目录");
		dirinfo.id = BROWER_TRASH;
		dirinfo.parent = NONE;
		dirinfo.bIsLeaf = false;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = true;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%CSIDL_INTERNET_CACHE%\\");  // 根据这个判断是否IE默认缓存是否被修改过
		dirinfo.strDirectory.push_back("%CSIDL_INTERNET_CACHE%\\Content.IE5");
		dirinfo.strDirectory.push_back("%CSIDL_INTERNET_CACHE%\\Content.MSO");
		dirinfo.strDirectory.push_back("%CSIDL_INTERNET_CACHE%\\Content.Outlook");
		dirinfo.strDirectory.push_back("%CSIDL_INTERNET_CACHE%\\Content.Word");
		dirinfo.strDirectory.push_back("%CSIDL_INTERNET_CACHE%\\AntiPhishing");
		dirinfo.strDirectory.push_back("%CSIDL_INTERNET_CACHE%\\Virtualized");
		dirinfo.strDirectory.push_back("%CSIDL_INTERNET_CACHE%\\Low");
		dirinfo.strFriendName = QStringLiteral("IE\\360\\腾讯TT\\傲游\\世界之窗\\搜狗浏览器");
		dirinfo.strExtArray.push_back("*");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = BROWER_IE;
		dirinfo.parent = BROWER_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = true;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%CSIDL_APPDATA%\\SogouExplorer\\Webkit\\Cache");
		dirinfo.strFriendName = QStringLiteral("搜狗浏览器（高速模式）");
		dirinfo.strExtArray.push_back("*");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = BROWER_SOGO;
		dirinfo.parent = BROWER_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = true;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%CSIDL_APPDATA%\\Maxthon3\\Temp\\Webkit\\Cache");
		dirinfo.strFriendName = QStringLiteral("傲游3（极速模式）");
		dirinfo.strExtArray.push_back("*");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = BROWER_MATHRON;
		dirinfo.parent = BROWER_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = true;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%firefox%");
		dirinfo.strFriendName = QStringLiteral("火狐（Firefox）");
		dirinfo.strExtArray.push_back("*");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = BROWER_FIREFOX;
		dirinfo.parent = BROWER_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = true;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%CSIDL_LOCAL_APPDATA%\\Google\\Chrome\\User Data\\Default\\cache");
		dirinfo.strDirectory.push_back("%CSIDL_LOCAL_APPDATA%\\Google\\Chrome\\User Data\\Default\\Media Cache");
		dirinfo.strFriendName = QStringLiteral("谷歌(Chrome)");
		dirinfo.strExtArray.push_back("*");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = BROWER_CHROME;
		dirinfo.parent = BROWER_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = true;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%CSIDL_LOCAL_APPDATA%\\Opera\\Opera\\opcache");
		dirinfo.strDirectory.push_back("%CSIDL_LOCAL_APPDATA%\\Opera\\Opera\\cache");
		dirinfo.strFriendName = "Opera";
		dirinfo.strExtArray.push_back("*");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = BROWER_OPERA;
		dirinfo.parent = BROWER_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strFriendName = QStringLiteral("视频播放缓存目录");
		dirinfo.id = VIDEO_TRASH;
		dirinfo.parent = NONE;
		dirinfo.bIsLeaf = false;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%CSIDL_LOCAL_APPDATA%\\Microsoft\\Media Player\\Transcoded Files Cache");
		dirinfo.strFriendName = "windows media player";
		dirinfo.strExtArray.push_back("*");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = VIDEO_MEDIA_PALYER;
		dirinfo.parent = VIDEO_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%pptv%");
		dirinfo.strFriendName = QStringLiteral("PPTV网络电视");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = VIDEO_PPTV;
		dirinfo.parent = VIDEO_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%qqlive%");
		dirinfo.strFriendName = QStringLiteral("QQLive网络电视");
		dirinfo.strExtArray.push_back("tdl");
		dirinfo.strExtArray.push_back("tdi");
		dirinfo.strExtArray.push_back("tii");
		dirinfo.strExtArray.push_back("tpt");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = VIDEO_QQLIVE;
		dirinfo.parent = VIDEO_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%xunleikankan%");
		dirinfo.strFriendName = QStringLiteral("迅雷看看");
		dirinfo.strExtArray.push_back("cfg");
		dirinfo.strExtArray.push_back("dat");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = VIDEO_XUNLEI;
		dirinfo.parent = VIDEO_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%fengxing%");
		dirinfo.strFriendName = QStringLiteral("风行网络电视");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = VIDEO_FENGXING;
		dirinfo.parent = VIDEO_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%youku%");
		dirinfo.strFriendName = QStringLiteral("优酷(iku)加速器");
		dirinfo.strExtArray.push_back("dat");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = VIDEO_YOUKU;
		dirinfo.parent = VIDEO_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%tudou%");
		dirinfo.strFriendName = QStringLiteral("飞速土豆");
		dirinfo.strExtArray.push_back("tdd!");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = VIDEO_TUDOU;
		dirinfo.parent = VIDEO_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%ku6%");
		dirinfo.strFriendName = QStringLiteral("极速酷6");
		dirinfo.strExtArray.push_back("k6p");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = VIDEO_KU6;
		dirinfo.parent = VIDEO_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%storm%");
		dirinfo.strFriendName = QStringLiteral("暴风影音");
		dirinfo.strExtArray.push_back("");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = VIDEO_STORM;
		dirinfo.parent = VIDEO_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%qvod%");
		dirinfo.strFriendName = QStringLiteral("Qvod播放器");
		dirinfo.strExtArray.push_back("!mv");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = VIDEO_QVOD;
		dirinfo.parent = VIDEO_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%ppstream%");
		dirinfo.strFriendName = QStringLiteral("PPS");
		dirinfo.strExtArray.push_back("ppsds.pgf");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = VIDEO_PPS;
		dirinfo.parent = VIDEO_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%qqmusic%");
		dirinfo.strFriendName = "QQMusic";
		dirinfo.strExtArray.push_back("tdl");
		dirinfo.strExtArray.push_back("tii");
		dirinfo.strExtArray.push_back("tdi");
		dirinfo.strExtArray.push_back("tpt");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = VIDEO_QQMUSIC;
		dirinfo.parent = VIDEO_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%kuwo%");
		dirinfo.strFriendName = "KUWO";
		dirinfo.strExtArray.push_back("wma");
		dirinfo.strExtArray.push_back("pack");
		dirinfo.strExtArray.push_back("mkv");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = VIDEO_KUWO;
		dirinfo.parent = VIDEO_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%kugoo%");
		dirinfo.strFriendName = "KuGoo";
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = VIDEO_KUGOO;
		dirinfo.parent = VIDEO_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%pipi%");
		dirinfo.strFriendName = "PIPIStream";
		dirinfo.strExtArray.push_back("jfrec");
		dirinfo.strExtArray.push_back("inpart");
		dirinfo.strExtArray.push_back("jfenc");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = VIDEO_PIPI;
		dirinfo.parent = VIDEO_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}
	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%CSIDL_APPDATA%\\TTPlayer\\cache");
		dirinfo.strFriendName = QStringLiteral("千千静听");
		dirinfo.strExtArray.push_back("*");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = VIDEO_TTPLAYER;
		dirinfo.parent = VIDEO_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	{
		ScanDirInfo dirinfo;
		dirinfo.bRecursive = true;
		dirinfo.bDefaultSelect = false;
		dirinfo.bRSelect = dirinfo.bDefaultSelect;
		dirinfo.strDirectory.push_back("%CSIDL_APPDATA%\\SogouExplorer\\SogouVideoCache");
		dirinfo.strDirectory.push_back("%sogou%");
		dirinfo.strFriendName = QStringLiteral("搜狗浏览器视频缓存");
		dirinfo.strExtArray.push_back("*");
		dirinfo.strFilt.push_back("%specfiles%");
		dirinfo.id = VIDEO_SOGOU;
		dirinfo.parent = VIDEO_TRASH;
		dirinfo.bIsLeaf = true;
		m_configData.push_back(dirinfo);
	}

	return convToLocatePath();
}

ScanDirInfo ConfigData::getItem(QString friendName)
{
	int count = m_configData.count();

	for (int i = 0; i < count; ++i) {
		const ScanDirInfo& info = m_configData.at(i);
		if (info.strFriendName == friendName) {
			return info;
		}
	}

	return ScanDirInfo();
}

