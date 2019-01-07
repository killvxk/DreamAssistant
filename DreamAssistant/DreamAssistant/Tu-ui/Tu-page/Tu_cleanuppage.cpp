#include "Tu_cleanuppage.h"
#include <QVBoxLayout>

CleanupPage::CleanupPage(QWidget *parent)
	: QWidget(parent)
{
	setFixedSize(900, 403);
	setAutoFillBackground(true);

	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(Qt::white));
	setPalette(palette);

	statked_widget = new QStackedWidget(this);
}

CleanupPage::~CleanupPage()
{

}

void CleanupPage::initUi(QString skin)
{
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(statked_widget);
	layout->setSpacing(0);
	layout->setMargin(0);
	layout->setContentsMargins(0, 0, 0, 0);
	setLayout(layout);
}

void CleanupPage::resetSkin(QString skin)
{

}

void CleanupPage::displayDetailPage()
{
	statked_widget->setCurrentIndex(1);
}

void CleanupPage::displayMainPage()
{
	statked_widget->setCurrentIndex(0);
	emit sig_clearDetailPage();
}
