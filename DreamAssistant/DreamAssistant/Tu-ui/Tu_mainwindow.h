#ifndef TU_MAINWINDOW_H
#define TU_MAINWINDOW_H

#include <QTranslator>
#include <QStackedWidget>

#include "./Tu-component/Tu_basedialog.h"
#include "./Tu-component/Tu_titlewidget.h"
#include "./Tu-component/Tu_toolwidget.h"
#include "./Tu-component/Tu_mainmenu.h"
#include "./Tu-component/Tu_loginwidget.h"
#include "./Tu-component/Tu_actionwidget.h"
#include "./Tu-component/Tu_contentwidget.h"

#include "./Tu-page/Tu_homeactionwidget.h"
#include "./Tu-page/Tu_homepage.h"
#include "./Tu-page/Tu_cleanupactionwidget.h"
#include "./Tu-page/Tu_cleanuppage.h"
#include "./Tu-page/Tu_evaluationactionwidget.h"
#include "./Tu-page/Tu_evaluationpage.h"
#include "./Tu-page/Tu_featureactionwidget.h"
#include "./Tu-page/Tu_featurepage.h"
#include "./Tu-page/Tu_toolkitsactionwidget.h"
#include "./Tu-page/Tu_toolkitspage.h"

#include "./Tu-dialog/Tu_aboutdialog.h"
#include "./Tu-dialog/Tu_upgradedialog.h"
#include "./Tu-dialog/Tu_skindialog.h"

#include "./Tu-utils/Tu_utils.h"
#include "./Tu-utils/Tu_common.h"

#include "../Tu-dbusproxy/Tu_sessiondispatcher.h"
#include "../Tu-dbusproxy/Tu_systemdispatcher.h"

class MainWindow : public BaseDialog
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

	void setTranslator(QTranslator* translator);

protected slots:
    void showMainMenu();
	void showAboutUsDialog();
	void showSkinDialog();

	void openUpgradePage();
	void openUpgradePageAgain();

	void closeDreamAssistant();

	void changeSkin(QString pciture);
	void restoreSkin();

	void reViewThePointSkin(QString pciture);
	void reViewTheOrgSkin();

	void upAnimFinished();
	void closeAnimFinished();

	void setCurrentPageIndex(int index);

private:
	void initActionWidget();
	void initContentWidget();
    void initFrame();
	void initTitle();
	void initTool();
	void initMainMenu();
	void initLoginWidget();

	void initHomePage();
	void initOtherPages();
	void initAnimation();

	void initValue();
	void loadSetting();

	void startDbusDaemon();

private:
	TitleWidget     *title_widget;
	ToolWidget      *tool_widget;
	MainMenu        *main_menu;
	LoginWidget     *login_widget;

	ActionWidget    *default_action_widget;
	ActionWidget    *other_action_widget;
	ContentWidget   *default_content_widget;
	ContentWidget   *other_content_widget;

	HomeActionWidget *home_action_widget;
	HomePage         *home_page;

	CleanupActionWidget *cleanup_action_widget;
	CleanupPage         *cleanup_page;

	EvaluationActionWidget *evaluation_action_widget;
	EvaluationPage       *evaluation_page;

	FeatureActionWidget *feature_action_widget;
	FeaturePage        *feature_page;

	ToolKitsActionWidget *toolkits_action_widget;
	ToolKitsPage     *toolkits_page;

	AboutDialog    *about_dialog;
	UpgradeDialog  *upgrade_dialog;
	SkinDialog     *skin_dialog;

	QStackedWidget *topStack;
	QStackedWidget *bottomStack;

	QSettings *mSettings;

	QPixmap main_skin_pixmap;
	QPixmap dream_skin_pixmap;

	QString last_skin_path;
	QString version;

	PAGESTATUS status;
	bool status_flag;

	QTranslator* translator;
	LANGUAGE current_language;

	SystemDispatcher *systeminterface;
	SessionDispatcher *sessioninterface;

	QParallelAnimationGroup *spreadGroup;
	QParallelAnimationGroup *gatherGroup;
};

#endif // TU_MAINWINDOW_H
