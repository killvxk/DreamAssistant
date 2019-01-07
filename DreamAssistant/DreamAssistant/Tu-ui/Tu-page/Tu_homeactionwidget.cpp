#include "Tu_homeactionwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDateTime>

#include "../Tu-utils/Tu_common.h"
#include "../Tu-dbusproxy/Tu_sessiondispatcher.h"
#include "../Tu-dbusproxy/Tu_systemdispatcher.h"

HomeActionWidget::HomeActionWidget(QWidget *parent, QSettings *mSettings)
	: QWidget(parent)
	, pSettings(mSettings)
	, m_trashSize(0)
	, m_clearSize(0)
{
	setFixedSize(900, 227);
	setAutoFillBackground(true);
	setObjectName("transparentWidget");

	initUi();
	initLayout();
	initConnect();
	setLanguage();
}

HomeActionWidget::~HomeActionWidget()
{

}

void HomeActionWidget::initUi()
{
	suggest_label = new QLabel;
	scan_result_label = new QLabel;
	result_label = new QLabel;
	doing_label = new QLabel;

	scan_button = new QPushButton(this);
	clean_button = new QPushButton(this);
	back_button = new QPushButton(this);

	loading_label = new LoadingLabel(this, "firstkey");
	loading_label->show();

	suggest_label->setObjectName("whiteLabel");
	suggest_label->setWordWrap(true);
	suggest_label->setFixedWidth(460);

	scan_result_label->setObjectName("whiteLabel");
	scan_result_label->setWordWrap(true);
	scan_result_label->setFixedWidth(460);
	scan_result_label->hide();

	result_label->setWordWrap(true);
	result_label->setObjectName("smallWhiteLabel");
	result_label->setFixedWidth(460);

	doing_label->setWordWrap(true);
	doing_label->setObjectName("whiteLabel");
	doing_label->hide();
	doing_label->setFixedWidth(460);

	scan_button->setGeometry(QRect(680, 100, 204, 65));
	scan_button->setFocusPolicy(Qt::NoFocus);
	QPixmap pixmap(":/res/home/scan.png");
	scan_button->setIcon(pixmap);
	scan_button->setIconSize(pixmap.size());
	scan_button->setObjectName("greenButton");
	scan_button->setEnabled(false);
	scan_button->show();

	clean_button->setGeometry(QRect(680, 100, 204, 65));
	clean_button->setFocusPolicy(Qt::NoFocus);
	clean_button->setObjectName("greenButton");
	clean_button->hide();

	back_button->setFocusPolicy(Qt::NoFocus);
	back_button->setGeometry(QRect(840, 170, 50, 30));
	back_button->setObjectName("backButton");
	back_button->setObjectName("underlineButton");
	back_button->hide();

	workFlag = this->getOneKeyFlag();
	if (workFlag.length() > 0) {
		if (workFlag == "1") {
			//clean
			dateStr = this->getFixCleanDate();
			result_label->setText(tr("The lastest cleanup time is ") + dateStr);
		} else if (workFlag == "0") {
			//scan
			dateStr = this->getSafeScanDate();
			result_label->setText(tr("The lastest scan time is ") + dateStr);
		}
	} else {
		result_label->setText(tr("You have not implemented the one key scan and clean-up operation."));
	}
}

void HomeActionWidget::initLayout()
{
	QVBoxLayout *layout1 = new QVBoxLayout;
	layout1->addStretch();
	layout1->addWidget(suggest_label);
	layout1->addWidget(scan_result_label);
	layout1->addWidget(doing_label);
	layout1->addWidget(result_label);
	layout1->addStretch();
	layout1->setSpacing(15);
	layout1->setContentsMargins(0, 20, 0, 0);

	QHBoxLayout *layout2 = new QHBoxLayout;
	layout2->addWidget(loading_label, 0, Qt::AlignHCenter);
	layout2->addLayout(layout1);
	layout2->setSpacing(20);
	layout2->setContentsMargins(0, 0, 0, 0);

	QHBoxLayout *main_layout = new QHBoxLayout;
	main_layout->addLayout(layout2);
	main_layout->addStretch();
	main_layout->setSpacing(0);
	main_layout->setMargin(0);
	main_layout->setContentsMargins(10, 30, 44, 0);

	setLayout(main_layout);
}

void HomeActionWidget::initConnect()
{
	connect(scan_button, &QPushButton::clicked, this, &HomeActionWidget::onStartButtonClicked);
	connect(clean_button, &QPushButton::clicked, this, &HomeActionWidget::onCleanButtonClicked);
	connect(back_button, &QPushButton::clicked, this, &HomeActionWidget::onEndButtonClicked);
}

void HomeActionWidget::setLanguage()
{
	suggest_label->setText(tr("Quick clean up system trash, saving disk space and improving the system efficiency!"));
	scan_button->setText(tr("Start Scan"));
	clean_button->setText(tr("Start Cleanup"));
	back_button->setText(tr("Back"));
	doing_label->setText(tr("Scanning......"));
}

void HomeActionWidget::enableScanButton()
{
	scan_button->setEnabled(true);
}

void HomeActionWidget::getScanResult(QString msg)
{
	QFontMetrics fontWidth(doing_label->font());
	QString nMsg = fontWidth.elidedText(msg, Qt::ElideRight, doing_label->width());

	QString text = QString("<p style=\"font-size:20px;\">%1<font size=\"1\">%2</font></p>")
		.arg(tr("Scanning: ")).arg(nMsg);

	doing_label->setText(text);
}

void HomeActionWidget::getScanDirItem(QStringList, QString, QString, quint64 size)
{
	m_trashSize += size;

	scan_result_label->setText(sizeToString(m_trashSize));
}

void HomeActionWidget::getRecycleBin(quint32, quint64 size)
{
	m_trashSize += size;

	scan_result_label->setText(sizeToString(m_trashSize));
}

void HomeActionWidget::finishScanResult(QString msg)
{
	if (msg != "onekey_scan_trash") {
		return;
	}

	doing_label->hide();
	result_label->show();

	result_label->setText(QString(tr("%1 trash, ready to cleanup")).arg(scan_result_label->text()));
	scan_result_label->setText(tr("Scan Over"));

	clean_button->show();
	clean_button->setEnabled(true);

	scanFinishTime = this->getCurrentDateTime();
	this->writeSafeScanDate();

	scan_button->hide();
	back_button->show();
	loading_label->stopLoading();
}

void HomeActionWidget::finishCleanResult(QString msg)
{
	this->writeFixCleanDate();

	scan_result_label->hide();
	result_label->show();
	result_label->setText(tr("The lastest cleanup time is ") + this->getCurrentDateTime());

	QString text = QString("<p style=\"font-size:20px;\">%1<font size=\"1\">%2</font></p>")
		.arg(tr("Cleanup Over: ")).arg(tr("%1 of garbage has been cleared.").arg(sizeToString(m_trashSize)));
	doing_label->setText(text);

	loading_label->stopLoading();
	scan_button->show();
	scan_button->setEnabled(true);
	clean_button->hide();
	clean_button->setEnabled(true);
	back_button->show();
}

void HomeActionWidget::getCleaningMessage(QString msg, quint64 size)
{
	QFontMetrics fontWidth(doing_label->font());
	QString nMsg = fontWidth.elidedText(msg, Qt::ElideRight, 500);

	QString text = QString("<p style=\"font-size:20px;\">%1<font size=\"1\">%2</font></p>")
		.arg(tr("Cleaning: ")).arg(nMsg);

	doing_label->setText(text);

	m_clearSize -= size;
	scan_result_label->setText(sizeToString(m_clearSize));
}

void HomeActionWidget::onStartButtonClicked()
{
	doing_label->setText(tr("Scanning......"));
	scan_button->setEnabled(false);
	loading_label->startLoading();
	suggest_label->hide();
	result_label->hide();
	doing_label->show();
	scan_result_label->show();

	m_trashSize = 0;
	sessionProxy->onekey_scan_function(QStringList());
}

void HomeActionWidget::onCleanButtonClicked()
{
	clean_button->hide();
	back_button->hide();
	loading_label->startLoading();
	suggest_label->hide();
	result_label->hide();
	doing_label->setText(tr("Ready to Cleanup......"));
	doing_label->show();
	
	m_clearSize = m_trashSize;
	sessionProxy->clean_trash_function(QStringList());
}

void HomeActionWidget::onEndButtonClicked()
{
	result_label->setText(tr("The lastest scan time is ") + scanFinishTime);
	loading_label->stopLoading();
	scan_button->show();
	scan_button->setEnabled(true);
	clean_button->hide();
	back_button->hide();
	suggest_label->show();
	scan_result_label->hide();
	result_label->show();
	doing_label->hide();
}

void HomeActionWidget::writeFixCleanDate()
{
	QDateTime time = QDateTime::currentDateTime();
	QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");

	pSettings->beginGroup("OneKeyClean");
	pSettings->setValue("CleanDate", str);
	pSettings->setValue("Flag", "1");
	pSettings->endGroup();
	pSettings->sync();
}

QString HomeActionWidget::getFixCleanDate()
{
	pSettings->beginGroup("OneKeyClean");
	QString value = pSettings->value("CleanDate").toString();
	pSettings->endGroup();
	pSettings->sync();

	return value;
}

QString HomeActionWidget::getCurrentDateTime()
{
	QDateTime time = QDateTime::currentDateTime();
	QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");

	return str;
}

void HomeActionWidget::writeSafeScanDate()
{
	QDateTime time = QDateTime::currentDateTime();
	QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");

	pSettings->beginGroup("OneKeyClean");
	pSettings->setValue("ScanDate", str);
	pSettings->setValue("Flag", "0");
	pSettings->endGroup();
	pSettings->sync();
}

QString HomeActionWidget::getSafeScanDate()
{
	pSettings->beginGroup("OneKeyClean");
	QString value = pSettings->value("ScanDate").toString();
	pSettings->endGroup();
	pSettings->sync();

	return value;
}

QString HomeActionWidget::getOneKeyFlag()
{
	pSettings->beginGroup("OneKeyClean");
	QString value = pSettings->value("Flag").toString();
	pSettings->endGroup();
	pSettings->sync();

	return value;
}
