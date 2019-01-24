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
		dirinfo.strFriendName = QStringLiteral("Windowsϵͳ�����ļ�");
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
		dirinfo.strFriendName = QStringLiteral("����վ");
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
		dirinfo.strFriendName = QStringLiteral("�û���ʱ�ļ���");
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
		dirinfo.strFriendName = QStringLiteral("Windows ��ʱĿ¼");
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
		dirinfo.strFriendName = QStringLiteral("����ͼ����");
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
		dirinfo.strFriendName = QStringLiteral("Windows���󱨸�");
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
		dirinfo.strFriendName = QStringLiteral("Windows ���²���");
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
		dirinfo.strFriendName = QStringLiteral("Windows Ԥ���ļ�");
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
		dirinfo.strFriendName = QStringLiteral("�����س����ļ�");
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
		dirinfo.strFriendName = QStringLiteral("�ڴ�ת���ļ�");
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
		dirinfo.strFriendName = QStringLiteral("ϵͳ��־�ļ�");
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
		dirinfo.strFriendName = QStringLiteral("Զ������");
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
		dirinfo.strFriendName = QStringLiteral("Office ��װ����Ŀ¼");
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
		dirinfo.strFriendName = QStringLiteral("ϵͳ�������ļ��������");
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
		dirinfo.strFriendName = QStringLiteral("���������Ŀ¼");
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
		dirinfo.strDirectory.push_back("%CSIDL_INTERNET_CACHE%\\");  // ��������ж��Ƿ�IEĬ�ϻ����Ƿ��޸Ĺ�
		dirinfo.strDirectory.push_back("%CSIDL_INTERNET_CACHE%\\Content.IE5");
		dirinfo.strDirectory.push_back("%CSIDL_INTERNET_CACHE%\\Content.MSO");
		dirinfo.strDirectory.push_back("%CSIDL_INTERNET_CACHE%\\Content.Outlook");
		dirinfo.strDirectory.push_back("%CSIDL_INTERNET_CACHE%\\Content.Word");
		dirinfo.strDirectory.push_back("%CSIDL_INTERNET_CACHE%\\AntiPhishing");
		dirinfo.strDirectory.push_back("%CSIDL_INTERNET_CACHE%\\Virtualized");
		dirinfo.strDirectory.push_back("%CSIDL_INTERNET_CACHE%\\Low");
		dirinfo.strFriendName = QStringLiteral("IE\\360\\��ѶTT\\����\\����֮��\\�ѹ������");
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
		dirinfo.strFriendName = QStringLiteral("�ѹ������������ģʽ��");
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
		dirinfo.strFriendName = QStringLiteral("����3������ģʽ��");
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
		dirinfo.strFriendName = QStringLiteral("�����Firefox��");
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
		dirinfo.strFriendName = QStringLiteral("�ȸ�(Chrome)");
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
		dirinfo.strFriendName = QStringLiteral("��Ƶ���Ż���Ŀ¼");
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
		dirinfo.strFriendName = QStringLiteral("PPTV�������");
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
		dirinfo.strFriendName = QStringLiteral("QQLive�������");
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
		dirinfo.strFriendName = QStringLiteral("Ѹ�׿���");
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
		dirinfo.strFriendName = QStringLiteral("�����������");
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
		dirinfo.strFriendName = QStringLiteral("�ſ�(iku)������");
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
		dirinfo.strFriendName = QStringLiteral("��������");
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
		dirinfo.strFriendName = QStringLiteral("���ٿ�6");
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
		dirinfo.strFriendName = QStringLiteral("����Ӱ��");
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
		dirinfo.strFriendName = QStringLiteral("Qvod������");
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
		dirinfo.strFriendName = QStringLiteral("ǧǧ����");
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
		dirinfo.strFriendName = QStringLiteral("�ѹ��������Ƶ����");
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

