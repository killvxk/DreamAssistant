#include "Tu_cleanupactionwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

CleanupActionWidget::CleanupActionWidget(QWidget *parent)
	: QWidget(parent)
{
	setFixedSize(900, 150);
	setAutoFillBackground(true);
	setObjectName("transparentWidget");

	initUi();
	initLayout();
	initConnect();
	setLanguage();
}

CleanupActionWidget::~CleanupActionWidget()
{

}

void CleanupActionWidget::initUi()
{
	suggest_label = new QLabel;
	doing_label = new QLabel;

	scan_button = new QPushButton(this);
	clean_button = new QPushButton(this);
	back_button = new QPushButton(this);

	back_button->setObjectName("backButton");
	back_button->hide();

	loading_label = new LoadingLabel(this, "clean");
	loading_label->show();

	suggest_label->setObjectName("whiteLabel");
	suggest_label->setWordWrap(true);
	suggest_label->setFixedWidth(550);

	doing_label->setFixedWidth(550);
	doing_label->setWordWrap(true);
	doing_label->setObjectName("whiteLabel");
	doing_label->hide();

	scan_button->setGeometry(QRect(690, 50, 182, 58));
	scan_button->setFocusPolicy(Qt::NoFocus);
	scan_button->setObjectName("greenButton");
	scan_button->show();

	clean_button->setGeometry(QRect(690, 50, 182, 58));
	clean_button->setFocusPolicy(Qt::NoFocus);
	clean_button->setObjectName("greenButton");
	clean_button->hide();

	back_button->setFocusPolicy(Qt::NoFocus);
	back_button->setGeometry(QRect(820, 110, 50, 30));
	back_button->setObjectName("underlineButton");
	back_button->hide();
}

void CleanupActionWidget::initLayout()
{
	QVBoxLayout *layout1 = new QVBoxLayout;
	layout1->addStretch();
	layout1->addWidget(suggest_label, 0, Qt::AlignVCenter);
	layout1->addWidget(doing_label, 0, Qt::AlignVCenter);
	layout1->addStretch();
	layout1->setSpacing(0);
	layout1->setContentsMargins(0, 0, 0, 0);

	QHBoxLayout *layout2 = new QHBoxLayout;
	layout2->addWidget(loading_label, 0, Qt::AlignVCenter);
	layout2->addLayout(layout1);
	layout2->setSpacing(20);
	layout2->setMargin(0);
	layout2->setContentsMargins(0, 0, 0, 0);

	QHBoxLayout *main_layout = new QHBoxLayout;
	main_layout->addLayout(layout2);
	main_layout->addStretch();
	main_layout->setSpacing(0);
	main_layout->setMargin(0);
	main_layout->setContentsMargins(13, 20, 44, 0);

	setLayout(main_layout);
}

void CleanupActionWidget::initConnect()
{
	connect(scan_button, &QPushButton::clicked, this, &CleanupActionWidget::onStartButtonClicked);
	connect(clean_button, &QPushButton::clicked, this, &CleanupActionWidget::onCleanButtonClicked);
	connect(back_button, &QPushButton::clicked, this, &CleanupActionWidget::onBackButtonClicked);
}

void CleanupActionWidget::setLanguage()
{
	suggest_label->setText(tr("Regular cleaning, let your computer remains the relaxed state"));
	scan_button->setText(tr("Start Scan"));
	clean_button->setText(tr("Start Cleanup"));
	back_button->setText(tr("Back"));
	doing_label->setText(tr("Scaning......"));
}

void CleanupActionWidget::showCleanOverStatus()
{
	loading_label->stopLoading();

	scan_button->show();
	scan_button->setEnabled(true);
	clean_button->hide();
	clean_button->setEnabled(true);
	back_button->hide();
	doing_label->setText(tr("Clean OK"));
}

void CleanupActionWidget::showCleanerData(const QStringList &data)
{
	if (data.length() == 2) {
		doing_label->setText(tr("Cleaning: ") + data.at(0).split(":").at(1));
	} else if (data.length() == 3) {
		doing_label->setText(data.at(0).split(":").at(1) + tr(", Percent is: ") + data.at(1).split(":").at(1) + tr("%, Status is: ") + data.at(2).split(":").at(1));
	}
}

void CleanupActionWidget::showCleanerStatus(const QString &status, const QString &domain)
{
	if (status == "Complete:History.firefox" && domain == "history") {
		doing_label->setText(tr("Clean Firefox history......"));
	} else if (status == "Complete:History.chromium" && domain == "history") {
		doing_label->setText(tr("Clean Chromium history......"));
	} else if (status == "Complete:History.system" && domain == "history") {
		doing_label->setText(tr("Clean system history......"));
	} else if (status == "Complete:" && domain == "apt") {
		doing_label->setText(tr("Clean apt......"));
	} else if (status == "Start:" && domain == "apt") {
		doing_label->setText(tr("Start clean apt......"));
	} else if (status == "Complete:Cookies.firefox") {
		doing_label->setText(tr("Clean Firefox Cookie:") + domain);
	} else if (status == "Complete:Cookies.chromium") {
		doing_label->setText(tr("Clean Chromium Cookie:") + domain);
	}
}

void CleanupActionWidget::showCleanerError(const QString &status)
{
	if (status.contains("Non-existent:")) {
		if (status.split(":").at(1).length() > 0)
			doing_label->setText(status.split(":").at(1) + tr(" does not exist"));
	} else if (status.contains("Working:Chromium")) {
		doing_label->setText(tr("Chromium Browser is running......"));
	}
}

void CleanupActionWidget::showCleanReciveStatus(const QString &status)
{
	if (status == "Complete:Cache") {
		doing_label->setText(tr("Cache Scan OK"));
	} else if (status == "Complete:Cookies") {
		doing_label->setText(tr("Cookies Scan OK"));
	} else if (status == "Complete:") {
		doing_label->setText(tr("History Scan OK"));
	} else if (status == "Complete:Packages") {
		doing_label->setText(tr("Packages Scan OK"));
	} else if (status == "Complete:All") {

	}
}

void CleanupActionWidget::accordScanOverStatusToChange(bool status)
{
	if (status) {
		doing_label->setText(tr("Scaning......"));
		doing_label->hide();
		loading_label->stopLoading();
		scan_button->hide();
		scan_button->setEnabled(true);
		clean_button->show();
		clean_button->setEnabled(true);
		suggest_label->show();
		back_button->show();
	} else {
		doing_label->setText(tr("Scaning......"));
		doing_label->hide();
		loading_label->stopLoading();
		scan_button->hide();
		scan_button->setEnabled(true);
		clean_button->hide();
		clean_button->setEnabled(true);
		suggest_label->show();
		back_button->show();
	}
}

void CleanupActionWidget::showCleanReciveError(const QString &status)
{
	doing_label->setText(tr("Error: ") + status);
	if (status == "Uninstalled:Firefox") {
		doing_label->setText(tr("Firefox Browser does not be installed"));
	} else if (status == "Uninstalled:Chromium") {
		doing_label->setText(tr("Chromium Browser does not be installed"));
	} else if (status == "Working:Chromium") {
		doing_label->setText(tr("Chromium Browser is running"));
	} else {
		if (status.contains("Non-existent:"))
			doing_label->setText(status.split(":").at(1) + tr(" does not exist"));
	}
}

void CleanupActionWidget::displayAnimation()
{
	scan_button->setEnabled(false);
	loading_label->startLoading();
	suggest_label->hide();
	doing_label->show();

	emit sig_showDetailData();
}

void CleanupActionWidget::receivePolicyKitSignal(bool status)
{
	/*display Clean Animation
	status = true:ok
	status = false:cacel
	*/
	if (status) //ok
	{
		clean_button->show();
		clean_button->setEnabled(false);
		back_button->hide();//0713
		scan_button->hide();
		loading_label->startLoading();
		suggest_label->hide();
		doing_label->setText(tr("Ready to Cleanup......"));
		doing_label->show();
	} else {
		clean_button->show();
		back_button->show();
	}
}

void CleanupActionWidget::displayOrgPage()
{
	doing_label->hide();
	back_button->hide();
	scan_button->show();
	scan_button->setEnabled(true);
	clean_button->hide();
	suggest_label->show();
}

void CleanupActionWidget::onStartButtonClicked()
{
	doing_label->setText(tr("Scaning......"));

	emit sig_sendScan();
}

void CleanupActionWidget::onCleanButtonClicked()
{
	clean_button->hide();
	back_button->hide();

	emit sig_sendClean();
}

void CleanupActionWidget::onBackButtonClicked()
{
	doing_label->hide();
	back_button->hide();
	loading_label->stopLoading();
	scan_button->show();
	scan_button->setEnabled(true);
	clean_button->hide();
	suggest_label->show();

	emit sig_showMainData();
}
