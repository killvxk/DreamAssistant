#include "Tu_featureactionwidget.h"
#include <QHBoxLayout>

FeatureActionWidget::FeatureActionWidget(QWidget *parent)
	: QWidget(parent)
{
	setFixedSize(900, 150);
	setAutoFillBackground(true);
	setObjectName("transparentWidget");

	initUi();
	initLayout();
	setLanguage();
}

FeatureActionWidget::~FeatureActionWidget()
{

}

void FeatureActionWidget::initUi()
{
	img_label = new QLabel;
	title_label = new QLabel;

	img_label->setScaledContents(true);

	QPixmap label_pixmap(":/res/feature/feature.png");
	img_label->setPixmap(label_pixmap);
	img_label->setFixedSize(label_pixmap.size());

	title_label->setObjectName("whiteLabel");
	title_label->setWordWrap(true);	
}

void FeatureActionWidget::initLayout()
{
	QHBoxLayout *layout = new QHBoxLayout;

	layout->addWidget(img_label, 0, Qt::AlignVCenter);
	layout->addWidget(title_label, 0, Qt::AlignVCenter);
	layout->setSpacing(20);
	layout->setMargin(0);
	layout->setContentsMargins(20, 20, 20, 0);

	setLayout(layout);
}

void FeatureActionWidget::setLanguage()
{
	title_label->setText(tr("You can perform a full range of customized systems based on personal preferences"));
}
