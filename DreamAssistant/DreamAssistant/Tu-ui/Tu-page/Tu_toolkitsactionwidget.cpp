#include "Tu_toolkitsactionwidget.h"
#include  <QHBoxLayout>

ToolKitsActionWidget::ToolKitsActionWidget(QWidget *parent)
	: QWidget(parent)
{
	setFixedSize(900, 150);
	setAutoFillBackground(true);
	setObjectName("transparentWidget");

	initUi();
	initLayout();
	setLanguage();
}

ToolKitsActionWidget::~ToolKitsActionWidget()
{

}

void ToolKitsActionWidget::initUi()
{
	img_label = new QLabel;
	title_label = new QLabel;
	more_btn = new QPushButton;

	img_label->setScaledContents(true);
	QPixmap label_pixmap(":/res/toolkits/toolkits.png");
	img_label->setPixmap(label_pixmap);
	img_label->setFixedSize(label_pixmap.size());

	title_label->setObjectName("whiteLabel");
	title_label->setWordWrap(true);

	more_btn->setFocusPolicy(Qt::NoFocus);
	more_btn->setObjectName("whiteButton");
	more_btn->hide();

	title_label->setMinimumWidth(500);
	title_label->setMaximumWidth(600);
}

void ToolKitsActionWidget::initLayout()
{
	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(img_label);
	layout->addWidget(title_label);
	layout->addWidget(more_btn);
	layout->addStretch();
	layout->setSpacing(15);
	layout->setContentsMargins(20, 20, 0, 0);
	setLayout(layout);
}

void ToolKitsActionWidget::setLanguage()
{
	title_label->setText(tr("Provide a practical and lightweight tool, create fast and convenient experience for you"));
	more_btn->setText(tr("More App"));
}
