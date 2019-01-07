#include <QTextCodec>
#include "Tu_mainwindow.h"
#include "../Tu-3rdparty/Tu-singleappliction/qtsingleapplication.h"
#include "Tu-utils/Tu_common.h"
#include <windows.h>
#include <DbgHelp.h>
#pragma comment(lib, "Dbghelp.lib")

LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
	HANDLE hDumpFile = CreateFile(L"crash.dmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hDumpFile != INVALID_HANDLE_VALUE) {
		MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
		dumpInfo.ExceptionPointers = pException;
		dumpInfo.ThreadId = GetCurrentThreadId();
		dumpInfo.ClientPointers = TRUE;

		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
	}

// 	MsgBox *msgbox = new MsgBox;
//     msgbox->setInfo(QObject::tr("Program crash"), QObject::tr("Express my sincere apologies for the mistake!"), QPixmap(":/msgbox/attention.png"), true);
// 	msgbox->exec();

	return EXCEPTION_EXECUTE_HANDLER;
}

int main(int argc, char *argv[])
{
	QtSingleApplication app("dream", argc, argv);
	if (app.isRunning()){
		app.sendMessage("raise_window_noop");
		return EXIT_SUCCESS;
	}

	QTextCodec *codec = QTextCodec::codecForName("System");
	QTextCodec::setCodecForLocale(codec);

	QString locale = QLocale::system().name();
	QTranslator translator;
	if (locale == "zh_CN" || locale == "en") {
		if (translator.load("dream_" + locale + ".qm", QCoreApplication::applicationDirPath() + "/translation/"))
			app.installTranslator(&translator);
	}

    qApp->setStyleSheet(appStyle());

	MainWindow w;
	app.setActivationWindow(&w);
	w.setTranslator(&translator);
	w.show();

	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);

	return app.exec();
}
