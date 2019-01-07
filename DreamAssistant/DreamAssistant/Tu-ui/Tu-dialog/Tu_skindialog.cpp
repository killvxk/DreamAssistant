#include "Tu_skindialog.h"
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QCoreApplication>
#include <QSignalMapper>
#include <QFileDialog>
#include <QDir>

#include "../Tu-dbusproxy/Tu_systemdispatcher.h"

SkinDialog::SkinDialog(QWidget *parent, QSettings *settings, QString skin)
	: BaseDialog(parent)
{
	setFixedSize(442, 340);
	setStyleSheet("QDialog{border: 1px solid white;border-radius:1px;background-color: #ffffff;}");
	setWindowFlags(Qt::FramelessWindowHint);

	last_skin_path = skin;
	mSettings = settings;
	aboutGroup = NULL;
	contributorGroup = NULL;

	initUi();
	initAnimation();
	initConnect();
	setLanguage();
}

SkinDialog::~SkinDialog()
{
	if (aboutGroup != NULL) {
		delete aboutGroup;
		aboutGroup = NULL;
	}

	if (contributorGroup != NULL) {
		delete contributorGroup;
		contributorGroup = NULL;
	}
}

void SkinDialog::initUi()
{
	baseWidget = new QWidget(this);
	baseWidget->setGeometry(QRect(0, 0, 442, 82));
	baseWidget->setAutoFillBackground(true);

	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(QPixmap(last_skin_path)));
	baseWidget->setPalette(palette);

	close_btn = new PushButton(baseWidget);
	close_btn->setFocusPolicy(Qt::NoFocus);
	close_btn->loadPixmap(":/res/title/close_button.png");

	label = new QLabel(baseWidget);
	label->setGeometry(QRect(71, 5, 300, 30));
	label->setStyleSheet("QLabel{color:#ffffff;font-family: 方正黑体_GBK;font-size: 13px;font-weight:bold;}");
	label->setAlignment(Qt::AlignCenter);

	skin_widget = new QWidget(this);
	skin_widget->setGeometry(QRect(15, 93, 420, 240));

	list_widget = NULL;
	custom_list_widget = NULL;

	sysBtn = new QPushButton(baseWidget);
	sysBtn->setGeometry(QRect(10, 50, 60, 24));

	customBtn = new QPushButton(baseWidget);
	customBtn->setGeometry(QRect(75, 50, 60, 24));

	indicator = new QLabel(baseWidget);
	indicator->setStyleSheet("QLabel{background-image:url(':/res/aboutus/underline.png');background-position:center;}");
	indicator->setGeometry(QRect(10, 75, 60, 2));

	sysBtn->setFocusPolicy(Qt::NoFocus);
	sysBtn->setObjectName("transparentButton");

	customBtn->setFocusPolicy(Qt::NoFocus);
	customBtn->setObjectName("transparentButton");

	sysBtn->setStyleSheet("QPushButton{background:transparent;font-family: 方正黑体_GBK;font-size:13px;color:#ffffff;}");
	customBtn->setStyleSheet("QPushButton{background:transparent;font-family: 方正黑体_GBK;font-size:13px;color:#ffffff;}");
}

void SkinDialog::initAnimation()
{
	QRect mainAcitonRect(10, 75, 60, 2);
	QRect origAcitonRect(75, 75, 60, 2);

	QPropertyAnimation *aboutAnimation = new QPropertyAnimation(indicator, "geometry");
	aboutAnimation->setDuration(300);
	aboutAnimation->setStartValue(origAcitonRect);
	aboutAnimation->setEndValue(mainAcitonRect);

	aboutGroup = new QParallelAnimationGroup(this);
	aboutGroup->addAnimation(aboutAnimation);

	QPropertyAnimation *contributorAnimation = new QPropertyAnimation(indicator, "geometry");
	contributorAnimation->setDuration(300);
	contributorAnimation->setStartValue(mainAcitonRect);
	contributorAnimation->setEndValue(origAcitonRect);

	contributorGroup = new QParallelAnimationGroup(this);
	contributorGroup->addAnimation(contributorAnimation);
}

void SkinDialog::initConnect()
{
	connect(close_btn, &PushButton::clicked, this, &SkinDialog::close);
	connect(sysBtn, &QPushButton::clicked, this, &SkinDialog::showSystem);
	connect(customBtn, &QPushButton::clicked, this, &SkinDialog::showCustom);
}

void SkinDialog::setLanguage()
{
	setWindowTitle(tr("Skin Setting"));

	label->setText(tr("Skin Setting"));
	sysBtn->setText(tr("Default"));
	customBtn->setText(tr("Custom"));
}

void SkinDialog::showSystem()
{
	aboutGroup->start();

	if (list_widget != NULL)
		list_widget->show();

	if (custom_list_widget != NULL)
		custom_list_widget->hide();
}

void SkinDialog::showCustom()
{
	contributorGroup->start();

	if (custom_list_widget != NULL)
		custom_list_widget->show();

	if (list_widget != NULL)
		list_widget->hide();
}

void SkinDialog::changeSkinCenterBackground(QString pciture)
{
	last_skin_path = pciture;

	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(QPixmap(last_skin_path)));
	baseWidget->setPalette(palette);

	emit sig_changeSkin(pciture);
}

void SkinDialog::changeEnterBackground(QString pciture)
{
	emit sig_reViewThePointSkin(pciture);

	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(QPixmap(pciture)));
	baseWidget->setPalette(palette);
}

void SkinDialog::changeLeaveBackground()
{
	emit sig_reViewTheOrgSkin();

	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(QPixmap(last_skin_path)));
	baseWidget->setPalette(palette);
}

void SkinDialog::deleteBackground(QString picture)
{
    bool result = systemProxy->delete_file(picture);

	if (result) {
		custom_list_widget->clear_card();
		this->reloadBackgroundList();

		QString conf_skin = this->getCurrentBackgroundAbsName();
		if (conf_skin == picture)
			this->changeSkinCenterBackground(DEFAULT_SKIN);
	}
}

void SkinDialog::initSysBackgroundList()
{
	list_widget = new CardWidget(130, 87, 10, this->skin_widget);
	list_widget->setGeometry(QRect(0, 0, 420, 240));
	list_widget->calculate_data();

	QDir picdir(QCoreApplication::applicationDirPath().append("/skin/default/"));
	picdir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	picdir.setSorting(QDir::Size | QDir::Reversed);

	QStringList filters;
	filters << "*.jpg" << "*.png";
	picdir.setNameFilters(filters);
	QFileInfoList list = picdir.entryInfoList();
	QString cur_skin = this->getCurrentBackgroundName();
	card_list.clear();

	QSignalMapper *signal_mapper = new QSignalMapper(this);
	for (int j = 0; j < list.size(); ++j) {
		QFileInfo fileInfo = list.at(j);
		ItemCard *card = new ItemCard(fileInfo.fileName(), false, list_widget->cardPanel);
		card_list.append(card);

		if (cur_skin == fileInfo.fileName())
			card->showUsingLogo(true);

		list_widget->add_card(card);
		connect(card, &ItemCard::sig_backgroundName, signal_mapper, static_cast<void(QSignalMapper::*)(void)>(&QSignalMapper::map));
		signal_mapper->setMapping(card, QString::number(j, 10));

		connect(card, &ItemCard::sig_backgroundName, this, &SkinDialog::changeSkinCenterBackground);
		connect(card, &ItemCard::sig_enterBackgroundSkin, this, &SkinDialog::changeEnterBackground);
		connect(card, &ItemCard::sig_leaveBackgroundSkin, this, &SkinDialog::changeLeaveBackground);
	}
	connect(signal_mapper, static_cast<void(QSignalMapper::*)(const QString &)>(&QSignalMapper::mapped), this, &SkinDialog::switchUsingLogo);

	custom_list_widget = new CardWidget(130, 87, 10, this->skin_widget);
	custom_list_widget->hide();
	custom_list_widget->setGeometry(QRect(0, 0, 420, 240));
	custom_list_widget->calculate_data();

	QDir customdir(QCoreApplication::applicationDirPath().append("/skin/custom/"));
	customdir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	customdir.setSorting(QDir::Size | QDir::Reversed);
	customdir.setNameFilters(filters);

	QFileInfoList custom_list = customdir.entryInfoList();
	QString cur_custom_skin = this->getCurrentBackgroundName();
	custom_card_list.clear();

	QSignalMapper *custom_mapper = new QSignalMapper(this);
	for (int j = 0; j < custom_list.size(); ++j) {
		QFileInfo fileInfo = custom_list.at(j);
		ItemCard *card = new ItemCard(fileInfo.fileName(), true, custom_list_widget->cardPanel);
		card->resetdislayDelBtnValue(true);
		custom_card_list.append(card);

		if (cur_custom_skin == fileInfo.fileName())
			card->showUsingLogo(true);

		custom_list_widget->add_card(card);
		connect(card, &ItemCard::sig_backgroundName, custom_mapper, static_cast<void(QSignalMapper::*)(void)>(&QSignalMapper::map));
		custom_mapper->setMapping(card, QString::number(j, 10));

		connect(card, &ItemCard::sig_backgroundName, this, &SkinDialog::changeSkinCenterBackground);
		connect(card, &ItemCard::sig_enterBackgroundSkin, this, &SkinDialog::changeEnterBackground);
		connect(card, &ItemCard::sig_leaveBackgroundSkin, this, &SkinDialog::changeLeaveBackground);
		connect(card, &ItemCard::sig_delteSkin, this, &SkinDialog::deleteBackground);
	}
	connect(custom_mapper, static_cast<void(QSignalMapper::*)(const QString &)>(&QSignalMapper::mapped), this, &SkinDialog::switchCusteomUsingLogo);

	ItemCard *card = new ItemCard(":/res/skin/create.png", true, custom_list_widget->cardPanel);
	custom_card_list.append(card);
	custom_list_widget->add_card(card);
	connect(card, &ItemCard::sig_addSkin, this, &SkinDialog::addCustomBackground);
}

void SkinDialog::reloadBackgroundList()
{
	custom_list_widget->setGeometry(QRect(0, 2, 500, 230));
	custom_list_widget->calculate_data();

	QDir picdir(QCoreApplication::applicationDirPath().append("/skin/custom/"));
	picdir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	picdir.setSorting(QDir::Size | QDir::Reversed);

	QStringList filters;
	filters << "*.jpg" << "*.png";
	picdir.setNameFilters(filters);

	QFileInfoList list = picdir.entryInfoList();
	QString cur_skin = this->getCurrentBackgroundName();

	custom_card_list.clear();
	QSignalMapper *signal_mapper = new QSignalMapper(this);
	for (int j = 0; j < list.size(); ++j) {
		QFileInfo fileInfo = list.at(j);
		ItemCard *card = new ItemCard(fileInfo.fileName(), true, custom_list_widget->cardPanel);
		card->resetdislayDelBtnValue(true);
		card->show();

		custom_card_list.append(card);
		if (cur_skin == fileInfo.fileName())
			card->showUsingLogo(true);

		custom_list_widget->add_card(card);
		connect(card, &ItemCard::sig_backgroundName, signal_mapper, static_cast<void(QSignalMapper::*)(void)>(&QSignalMapper::map));
		signal_mapper->setMapping(card, QString::number(j, 10));

		connect(card, &ItemCard::sig_backgroundName, this, &SkinDialog::changeSkinCenterBackground);
		connect(card, &ItemCard::sig_enterBackgroundSkin, this, &SkinDialog::changeEnterBackground);
		connect(card, &ItemCard::sig_leaveBackgroundSkin, this, &SkinDialog::changeLeaveBackground);
		connect(card, &ItemCard::sig_delteSkin, this, &SkinDialog::deleteBackground);
	}
	connect(signal_mapper, static_cast<void(QSignalMapper::*)(const QString &)>(&QSignalMapper::mapped), this, &SkinDialog::switchUsingLogo);

	ItemCard *card = new ItemCard(":/res/skin/create.png", true, custom_list_widget->cardPanel);
	card->show();
	custom_card_list.append(card);
	custom_list_widget->add_card(card);
	connect(card, &ItemCard::sig_addSkin, this, &SkinDialog::addCustomBackground);
}

void SkinDialog::addCustomBackground()
{
	QStringList fileNameList;
	QString fileName;

	QFileDialog* fd = new QFileDialog(this);
	fd->resize(500, 471);
	fd->setNameFilter(tr("Image Files(*.jpg *.png)"));
	fd->setViewMode(QFileDialog::List);

	if (fd->exec() == QDialog::Accepted)
	{
		fileNameList = fd->selectedFiles();
		fileName = fileNameList[0];

        bool result = systemProxy->copy_file(fileName);
		if (result == true) {
			custom_list_widget->clear_card();
			this->reloadBackgroundList();
			int  start_pos = fileName.lastIndexOf("/") + 1;
			int end_pos = fileName.length();
			QString icon_name = QCoreApplication::applicationDirPath().append("skin/custom/");
			QString abs_name = icon_name.append(fileName.mid(start_pos, end_pos - start_pos));

			this->changeSkinCenterBackground(abs_name);

			//change custom using logo
			for (int i = 0; i < custom_card_list.count() - 1; i++) {
				ItemCard *card = custom_card_list.at(i);
				if (card->getCardName() == abs_name) {
					card->showUsingLogo(true);
				} else {
					card->showUsingLogo(false);
				}
			}

			//change system using logo
			for (int i = 0; i < card_list.count(); i++) {
				ItemCard *card = card_list.at(i);
				card->showUsingLogo(false);
			}
		}
	}
	else
		fd->close();
}

void SkinDialog::switchUsingLogo(QString index)
{
	int current_index = index.toInt(0);

	for (int i = 0; i < card_list.count(); i++) {
		ItemCard *card = card_list.at(i);
		if (current_index == i) {
			card->showUsingLogo(true);
		} else {
			card->showUsingLogo(false);
		}
	}

	//change custom using logo
	for (int i = 0; i < custom_card_list.count() - 1; i++) {
		ItemCard *card = custom_card_list.at(i);
		card->showUsingLogo(false);
	}
}

void SkinDialog::switchCusteomUsingLogo(QString index)
{
	int current_index = index.toInt(0);

	for (int i = 0; i < custom_card_list.count(); i++) {
		ItemCard *card = custom_card_list.at(i);
		if (current_index == i) {
			card->showUsingLogo(true);
		} else {
			card->showUsingLogo(false);
		}
	}

	//change ystem using logo
	for (int i = 0; i < card_list.count(); i++) {
		ItemCard *card = card_list.at(i);
		card->showUsingLogo(false);
	}
}

QString SkinDialog::getCurrentBackgroundName()
{
	QString cur_skin_path;
	mSettings->beginGroup("Background");
	cur_skin_path = mSettings->value("Path").toString();

	if (!cur_skin_path.isEmpty()) {
		int  start_pos = cur_skin_path.lastIndexOf("/") + 1;
		int end_pos = cur_skin_path.length();
		cur_skin_path = cur_skin_path.mid(start_pos, end_pos - start_pos);
	}

	mSettings->endGroup();
	mSettings->sync();

	return cur_skin_path;
}

QString SkinDialog::getCurrentBackgroundAbsName()
{
	QString cur_skin_path;

	mSettings->beginGroup("Background");
	cur_skin_path = mSettings->value("Path").toString();
	mSettings->endGroup();
	mSettings->sync();

	return cur_skin_path;
}

void SkinDialog::closeEvent(QCloseEvent *event)
{
	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(QPixmap(last_skin_path)));
	baseWidget->setPalette(palette);

	emit sig_restoreSkin();
}
