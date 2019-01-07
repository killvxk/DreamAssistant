#include "Tu_mainwindow.h"
#include <QPropertyAnimation>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
	: BaseDialog(parent)
{
	initValue();
	loadSetting();

    initFrame();
	initActionWidget();
	initContentWidget();

	initTitle();
	initTool();
	initMainMenu();
	initLoginWidget();

	initHomePage();
	initAnimation();

	startDbusDaemon();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initValue()
{
	skin_dialog = NULL;
	about_dialog = NULL;
	upgrade_dialog = NULL;

	login_widget = NULL;

	home_page = NULL;
	home_action_widget = NULL;
	cleanup_action_widget = NULL;
	cleanup_page = NULL;
	evaluation_page = NULL;
	evaluation_action_widget = NULL;
	feature_page = NULL;
	feature_action_widget = NULL;
	toolkits_page = NULL;
	toolkits_action_widget = NULL;

	spreadGroup = NULL;
	gatherGroup = NULL;

	version = "V2.0.5";

	status_flag = false;

	status = HOMEPAGE;
}

void MainWindow::initFrame()
{
    setFixedSize(900, 600);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint);

    setWindowTitle(tr("DreamAssistant"));

    setStyleSheet("QDialog{border:1px solid white; border-radius:1px; background-color:#ffffff;}");
}

void MainWindow::initActionWidget()
{
	default_action_widget = new ActionWidget(this);
	default_action_widget->setGeometry(QRect(0, 0, 900, 227));
	default_action_widget->setFixedHeight(227);

	other_action_widget = new ActionWidget(this);
	other_action_widget->setGeometry(QRect(0, -150, 900, 150));
	other_action_widget->setFixedHeight(150);

	topStack = new QStackedWidget(other_action_widget);
	topStack->setGeometry(other_action_widget->rect());

	QPalette palette_back;
	palette_back.setBrush(QPalette::Background, QBrush(QPixmap(last_skin_path)));
	default_action_widget->setPalette(palette_back);
	other_action_widget->setPalette(palette_back);
}

void MainWindow::initContentWidget()
{
	default_content_widget = new ContentWidget(this);
	default_content_widget->setGeometry(QRect(0, 274, 900, 326));
	default_content_widget->setFixedHeight(326);

	other_content_widget = new ContentWidget(this);
	other_content_widget->setGeometry(QRect(0, 600, 900, 403));
	other_content_widget->setFixedHeight(403);

	bottomStack = new QStackedWidget(other_content_widget);
	bottomStack->setGeometry(other_content_widget->rect());
}

void MainWindow::initTitle()
{
	title_widget = new TitleWidget(this);
	title_widget->move(0, 0);

	connect(title_widget, &TitleWidget::sig_showMinimized, this, &MainWindow::showMinimized);
	connect(title_widget, &TitleWidget::sig_showMainMenu, this, &MainWindow::showMainMenu);
	connect(title_widget, &TitleWidget::sig_showSkinCenter, this, &MainWindow::showSkinDialog);
	connect(title_widget, &TitleWidget::sig_closeApp, this, &MainWindow::closeDreamAssistant);
}

void MainWindow::initTool()
{
	tool_widget = new ToolWidget(this);
	tool_widget->setGeometry(QRect(0, 227, 900, 47));

	connect(tool_widget, &ToolWidget::sig_turnCurrentPage, this, &MainWindow::setCurrentPageIndex);
}

void MainWindow::initMainMenu()
{
	main_menu = new MainMenu(this);

	connect(main_menu, &MainMenu::sig_showUpgradePage, this, &MainWindow::openUpgradePage);
	connect(main_menu, &MainMenu::sig_aboutUs, this, &MainWindow::showAboutUsDialog);
}

void MainWindow::initLoginWidget()
{
	login_widget = new LoginWidget(this);
	login_widget->move(585, 0);
}

void MainWindow::initHomePage()
{
	if (home_action_widget == NULL) {
		QGridLayout *home_top_grid_layout = new QGridLayout;

		home_action_widget = new HomeActionWidget(0, mSettings);

		home_top_grid_layout->addWidget(home_action_widget, 0, 0);
        home_top_grid_layout->setSpacing(0);
        home_top_grid_layout->setContentsMargins(0, 0, 0, 0);
		default_action_widget->setLayout(home_top_grid_layout);
	}

	if (home_page == NULL) {
		QGridLayout *home_bottom_grid_layout = new QGridLayout;
		home_page = new HomePage(0, version);

		connect(home_page, &HomePage::sig_moreSignal, tool_widget, &ToolWidget::showBoxTool);
		connect(home_page, &HomePage::sig_sendSignal, tool_widget, &ToolWidget::showBoxTool);

		home_bottom_grid_layout->addWidget(home_page, 0, 0);
		home_bottom_grid_layout->setSpacing(0);
		home_bottom_grid_layout->setContentsMargins(0, 0, 0, 0);
        default_content_widget->setLayout(home_bottom_grid_layout);
	}
}

void MainWindow::initOtherPages()
{
	if (cleanup_action_widget == NULL)
		cleanup_action_widget = new CleanupActionWidget(this);
	topStack->addWidget(cleanup_action_widget);
	if (evaluation_action_widget == NULL)
		evaluation_action_widget = new EvaluationActionWidget(this);
	topStack->addWidget(evaluation_action_widget);
	if (feature_action_widget == NULL)
		feature_action_widget = new FeatureActionWidget(this);
	topStack->addWidget(feature_action_widget);
	if (toolkits_action_widget == NULL)
		toolkits_action_widget = new ToolKitsActionWidget(this);
	topStack->addWidget(toolkits_action_widget);

	if (cleanup_page == NULL)
		cleanup_page = new CleanupPage(this);
	cleanup_page->initUi(last_skin_path);
	bottomStack->addWidget(cleanup_page);
	if (evaluation_page == NULL)
		evaluation_page = new EvaluationPage(this);
	bottomStack->addWidget(evaluation_page);
	if (feature_page == NULL)
		feature_page = new FeaturePage(this);
	bottomStack->addWidget(feature_page);
	if (toolkits_page == NULL)
		toolkits_page = new ToolKitsPage(this, QCoreApplication::applicationDirPath());
	bottomStack->addWidget(toolkits_page);

	connect(cleanup_action_widget, &CleanupActionWidget::sig_sendScan, cleanup_page, &CleanupPage::sig_transScan);
	connect(cleanup_page, &CleanupPage::sig_tranActionAnimaiton, cleanup_action_widget, &CleanupActionWidget::displayAnimation);
}

void MainWindow::initAnimation()
{
	QPoint origPoint(0, 227);
	QPoint needPoint(0, 150);
	QPoint origPoint1(0, 0);
	QPoint needPoint1(0, -227);
	QPoint origPoint2(0, -150);
	QPoint needPoint2(0, 0);

	QPoint origPoint3(0, 274);
	QPoint needPoint3(0, 600);
	QPoint origPoint4(0, 600);
	QPoint needPoint4(0, 197);

	QPropertyAnimation *mainActionAnimation = new QPropertyAnimation(default_action_widget, "pos");
	mainActionAnimation->setDuration(500);
	mainActionAnimation->setStartValue(origPoint1);
	mainActionAnimation->setEndValue(needPoint1);

	QPropertyAnimation *mainActionAnimation2 = new QPropertyAnimation(other_action_widget, "pos");
	mainActionAnimation2->setDuration(500);
	mainActionAnimation2->setStartValue(origPoint2);
	mainActionAnimation2->setEndValue(needPoint2);

	QPropertyAnimation *mainToolAnimation = new QPropertyAnimation(tool_widget, "pos");
	mainToolAnimation->setDuration(500);
	mainToolAnimation->setStartValue(origPoint);
	mainToolAnimation->setEndValue(needPoint);

	QPropertyAnimation *mainContentAnimation = new QPropertyAnimation(default_content_widget, "pos");
	mainContentAnimation->setDuration(500);
	mainContentAnimation->setStartValue(origPoint3);
	mainContentAnimation->setEndValue(needPoint3);

	QPropertyAnimation *mainContentAnimation2 = new QPropertyAnimation(other_content_widget, "pos");
	mainContentAnimation2->setDuration(500);
	mainContentAnimation2->setStartValue(origPoint4);
	mainContentAnimation2->setEndValue(needPoint4);

	spreadGroup = new QParallelAnimationGroup(this);
	spreadGroup->addAnimation(mainActionAnimation);
	spreadGroup->addAnimation(mainActionAnimation2);
	spreadGroup->addAnimation(mainToolAnimation);
	spreadGroup->addAnimation(mainContentAnimation);
	spreadGroup->addAnimation(mainContentAnimation2);

	QPropertyAnimation *mainActionBackAnimation2 = new QPropertyAnimation(other_action_widget, "pos");
	mainActionBackAnimation2->setDuration(500);
	mainActionBackAnimation2->setStartValue(needPoint2);
	mainActionBackAnimation2->setEndValue(origPoint2);

	QPropertyAnimation *mainActionBackAnimation = new QPropertyAnimation(default_action_widget, "pos");
	mainActionBackAnimation->setDuration(500);
	mainActionBackAnimation->setStartValue(needPoint1);
	mainActionBackAnimation->setEndValue(origPoint1);

	QPropertyAnimation *mainToolBackAnimation = new QPropertyAnimation(tool_widget, "pos");
	mainToolBackAnimation->setDuration(500);
	mainToolBackAnimation->setStartValue(needPoint);
	mainToolBackAnimation->setEndValue(origPoint);


	QPropertyAnimation *mainContentBackAnimation = new QPropertyAnimation(default_content_widget, "pos");
	mainContentBackAnimation->setDuration(500);
	mainContentBackAnimation->setStartValue(needPoint3);
	mainContentBackAnimation->setEndValue(origPoint3);

	QPropertyAnimation *mainContentBackAnimation2 = new QPropertyAnimation(other_content_widget, "pos");
	mainContentBackAnimation2->setDuration(500);
	mainContentBackAnimation2->setStartValue(needPoint4);
	mainContentBackAnimation2->setEndValue(origPoint4);

	gatherGroup = new QParallelAnimationGroup(this);
	gatherGroup->addAnimation(mainActionBackAnimation);
	gatherGroup->addAnimation(mainActionBackAnimation2);
	gatherGroup->addAnimation(mainToolBackAnimation);
	gatherGroup->addAnimation(mainContentBackAnimation);
	gatherGroup->addAnimation(mainContentBackAnimation2);

	connect(spreadGroup, &QParallelAnimationGroup::finished, this, &MainWindow::upAnimFinished);
	connect(gatherGroup, &QParallelAnimationGroup::finished, this, &MainWindow::closeAnimFinished);
}

void MainWindow::loadSetting()
{
	mSettings = new QSettings(DREAM_COMPANY_SETTING, DREAM_SETTING_FILE_NAME_SETTING);
	mSettings->setIniCodec("UTF-8");

	mSettings->beginGroup("Background");
	last_skin_path = mSettings->value("Path").toString();

	if (last_skin_path.isEmpty()) {
		last_skin_path = DEFAULT_SKIN;
		mSettings->setValue("Path", last_skin_path);
	} else {
		QStringList skinlist = filterSkin();
		QList<QString>::Iterator it = skinlist.begin(), itend = skinlist.end();
		bool flag = false;

		for (; it != itend; it++) {
			if (*it == last_skin_path) {
				flag = true;
				break;
			}
		}
		if (flag == false) {
			mSettings->setValue("Path", last_skin_path);
		}
	}

	mSettings->endGroup();
	mSettings->sync();
	main_skin_pixmap.load(last_skin_path);
}

void MainWindow::startDbusDaemon()
{
	sessioninterface = new SessionDispatcher(this);
	systeminterface = new SystemDispatcher(this);

	home_action_widget->setSessionDbusProxy(sessioninterface);
	home_action_widget->setSystemDbusProxy(systeminterface);
	home_action_widget->enableScanButton();

	connect(sessioninterface, &SessionDispatcher::sig_isScanning, home_action_widget, &HomeActionWidget::getScanResult);
	connect(sessioninterface, &SessionDispatcher::sig_scanDirItem, home_action_widget, &HomeActionWidget::getScanDirItem);
	connect(sessioninterface, &SessionDispatcher::sig_recycleBin, home_action_widget, &HomeActionWidget::getRecycleBin);
	connect(sessioninterface, &SessionDispatcher::sig_finishScanWork, home_action_widget, &HomeActionWidget::finishScanResult);

	connect(sessioninterface, &SessionDispatcher::sig_deleteFile, home_action_widget, &HomeActionWidget::getCleaningMessage);
	connect(sessioninterface, &SessionDispatcher::sig_finishCleanWork, home_action_widget, &HomeActionWidget::finishCleanResult);

	initOtherPages();
}

void MainWindow::openUpgradePage()
{
	int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (334 / 2);
	int w_y = this->frameGeometry().topLeft().y() + (600 / 2) - (470 / 2);

	if (upgrade_dialog == NULL) {
		upgrade_dialog = new UpgradeDialog(0, this->version, last_skin_path);
		upgrade_dialog->checkLastestVersion();

		connect(home_page, &HomePage::sig_sendOpenUpgrade, this, &MainWindow::openUpgradePageAgain);
		connect(upgrade_dialog, &UpgradeDialog::sig_showBackendBtn, home_page, &HomePage::displayBackedBtn);
		connect(upgrade_dialog, &UpgradeDialog::sig_close, this, &MainWindow::closeDreamAssistant);
	}

	upgrade_dialog->move(w_x, w_y);
	upgrade_dialog->show();
	upgrade_dialog->raise();
	home_page->hideBackedBtn();
}

void MainWindow::openUpgradePageAgain()
{
	int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (334 / 2);
	int w_y = this->frameGeometry().topLeft().y() + (600 / 2) - (470 / 2);

	upgrade_dialog->move(w_x, w_y);
	upgrade_dialog->show();
	upgrade_dialog->raise();
}

void MainWindow::showMainMenu()
{
	QPoint p = rect().topLeft();
	p.setX(p.x() + 107);
	p.setY(p.y() + 22);

	main_menu->exec(this->mapToGlobal(p));
}

void MainWindow::showAboutUsDialog()
{
	int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (442 / 2);
	int w_y = this->frameGeometry().topLeft().y() + (600 / 2) - (326 / 2);

	if (about_dialog == NULL) {
		about_dialog = new AboutDialog(0, version, last_skin_path);
	}

	about_dialog->move(w_x, w_y);
	about_dialog->show();
	about_dialog->raise();
}

void MainWindow::showSkinDialog()
{
	int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (442 / 2);
	int w_y = this->frameGeometry().topLeft().y() + (600 / 2) - (326 / 2);

	if (skin_dialog == NULL) {
		skin_dialog = new SkinDialog(0, mSettings, last_skin_path);

		connect(skin_dialog, &SkinDialog::sig_changeSkin, this, &MainWindow::changeSkin);
		connect(skin_dialog, &SkinDialog::sig_restoreSkin, this, &MainWindow::restoreSkin);
		connect(skin_dialog, &SkinDialog::sig_reViewTheOrgSkin, this, &MainWindow::reViewTheOrgSkin);
		connect(skin_dialog, &SkinDialog::sig_reViewThePointSkin, this, &MainWindow::reViewThePointSkin);

		skin_dialog->setSystemDbusProxy(systeminterface);
		skin_dialog->initSysBackgroundList();
	}

	skin_dialog->move(w_x, w_y);
	skin_dialog->show();
	skin_dialog->raise();
}

void MainWindow::closeDreamAssistant()
{
	QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
	animation->setDuration(500);
	animation->setStartValue(1);
	animation->setEndValue(0);
	animation->start();

	connect(animation, &QPropertyAnimation::finished, this, &MainWindow::close);
}

void MainWindow::setCurrentPageIndex(int index)
{
	switch (index)
	{
	case 0:
		if (status != HOMEPAGE) {
			status_flag = true;
			tool_widget->hide();

			if (title_widget->isVisible())
				title_widget->hide();

			if (login_widget->isVisible())
				login_widget->hide();

			gatherGroup->start();
			status = HOMEPAGE;
		} else
			status_flag = false;
		break;
	case 1:
		if (status == HOMEPAGE) {
			status_flag = true;
		} else {
			status_flag = false;
		}

		if (status != CLEANUPPAGE && status_flag) {
			tool_widget->hide();

			if (title_widget->isVisible())
				title_widget->hide();

			if (login_widget->isVisible())
				login_widget->hide();

			topStack->setCurrentWidget(cleanup_action_widget);
			bottomStack->setCurrentWidget(cleanup_page);
			spreadGroup->start();

			status = CLEANUPPAGE;
		} else {
			if (login_widget->isVisible())
				login_widget->hide();

			topStack->setCurrentWidget(cleanup_action_widget);
			bottomStack->setCurrentWidget(cleanup_page);
		}
		break;
	case 2:
		if (status == HOMEPAGE) {
			status_flag = true;
		} else {
			status_flag = false;
		}
		if (status != EVALUATIONPAGE && status_flag) {
			tool_widget->hide();

			if (title_widget->isVisible())
				title_widget->hide();
			if (login_widget->isVisible())
				login_widget->hide();

			topStack->setCurrentWidget(evaluation_action_widget);
			bottomStack->setCurrentWidget(evaluation_page);
			spreadGroup->start();
			status = EVALUATIONPAGE;
		} else {
			if (login_widget->isVisible())
				login_widget->hide();

			topStack->setCurrentWidget(evaluation_action_widget);
			bottomStack->setCurrentWidget(evaluation_page);
		}
		break;
	case 3:
		if (status == HOMEPAGE)
			status_flag = true;
		else
			status_flag = false;

		if (status != FEATUREPAGE && status_flag) {
			tool_widget->hide();

			if (title_widget->isVisible())
				title_widget->hide();

			if (login_widget->isVisible())
				login_widget->hide();

			topStack->setCurrentWidget(feature_action_widget);
			bottomStack->setCurrentWidget(feature_page);
			spreadGroup->start();
			status = FEATUREPAGE;
		} else {
			if (login_widget->isVisible())
				login_widget->hide();

			topStack->setCurrentWidget(feature_action_widget);
			bottomStack->setCurrentWidget(feature_page);
		}
		break;
	case 4:
		if (status == HOMEPAGE)
			status_flag = true;
		else
			status_flag = false;

		if (status != TOOLKITSPAGE && status_flag) {
			tool_widget->hide();

			if (title_widget->isVisible())
				title_widget->hide();

			if (login_widget->isVisible())
				login_widget->hide();

			topStack->setCurrentWidget(toolkits_action_widget);
			bottomStack->setCurrentWidget(toolkits_page);
			spreadGroup->start();
			status = TOOLKITSPAGE;
		} else {
			if (login_widget->isHidden())
				login_widget->show();

			topStack->setCurrentWidget(toolkits_action_widget);
			bottomStack->setCurrentWidget(toolkits_page);
		}
		break;
	default:
		break;
	}
}

void MainWindow::changeSkin(QString pciture)
{
	if (main_skin_pixmap.isDetached()) {
		main_skin_pixmap.detach();
	}

	last_skin_path = pciture;
	main_skin_pixmap.load(pciture);

	QPalette palette;
	palette.setBrush(QPalette::Background, main_skin_pixmap);
	default_action_widget->setPalette(palette);
	other_action_widget->setPalette(palette);

	mSettings->beginGroup("Background");
	mSettings->setValue("Path", pciture);
	mSettings->endGroup();
	mSettings->sync();

	if (about_dialog != NULL) {
		about_dialog->resetTitleSkin(last_skin_path);
	}
	if (upgrade_dialog != NULL) {
		upgrade_dialog->resetTitleSkin(last_skin_path);
	}
}

void MainWindow::restoreSkin()
{
	if (main_skin_pixmap.isDetached()) {
		main_skin_pixmap.detach();
	}
	main_skin_pixmap.load(last_skin_path);

	QPalette palette_back;
	palette_back.setBrush(QPalette::Background, main_skin_pixmap);

	default_action_widget->setPalette(palette_back);
	other_action_widget->setPalette(palette_back);
}

void MainWindow::reViewThePointSkin(QString pciture)
{
	if (dream_skin_pixmap.isDetached()) {
		dream_skin_pixmap.detach();
	}
	dream_skin_pixmap.load(pciture);

	QPalette palette_back;
	palette_back.setBrush(QPalette::Background, dream_skin_pixmap);

	default_action_widget->setPalette(palette_back);
	other_action_widget->setPalette(palette_back);
}

void MainWindow::reViewTheOrgSkin()
{
	if (dream_skin_pixmap.isDetached()) {
		dream_skin_pixmap.detach();
	}
	dream_skin_pixmap.load(last_skin_path);

	QPalette palette_back;
	palette_back.setBrush(QPalette::Background, dream_skin_pixmap);
	default_action_widget->setPalette(palette_back);
	other_action_widget->setPalette(palette_back);
}

void MainWindow::upAnimFinished()
{
	tool_widget->show();

	if (title_widget->isHidden())
		title_widget->show();

	if (status == TOOLKITSPAGE && login_widget->isHidden())
		login_widget->show();
	else
		login_widget->hide();
}

void MainWindow::closeAnimFinished()
{
	tool_widget->show();

	if (title_widget->isHidden())
		title_widget->show();

	if (login_widget->isHidden())
		login_widget->show();
}

void MainWindow::setTranslator(QTranslator* translator)
{
	this->translator = translator;
}
