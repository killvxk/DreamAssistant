#include "Tu_evaluationactionwidget.h"
#include <QHBoxLayout>

EvaluationActionWidget::EvaluationActionWidget(QWidget *parent)
	: QWidget(parent)
{
	setFixedSize(900, 150);
	setAutoFillBackground(true);
	setObjectName("transparentWidget");

	initUi();
	initLayout();
	setLanguage();
}

EvaluationActionWidget::~EvaluationActionWidget()
{

}

void EvaluationActionWidget::initUi()
{
	img_label = new QLabel;
	title_label = new QLabel;

	img_label->setScaledContents(true);

	QPixmap label_pixmap(":/res/evaluation/evaluation.png");
	img_label->setPixmap(label_pixmap);
	img_label->setFixedSize(label_pixmap.size());

	title_label->setObjectName("whiteLabel");
	title_label->setWordWrap(true);
}

void EvaluationActionWidget::initLayout()
{
	QHBoxLayout *layout = new QHBoxLayout;

	layout->addWidget(img_label, 0, Qt::AlignVCenter);
	layout->addWidget(title_label, 0, Qt::AlignVCenter);
	layout->setSpacing(20);
	layout->setMargin(0);
	layout->setContentsMargins(20, 20, 20, 0);

	setLayout(layout);
}

void EvaluationActionWidget::setLanguage()
{
	title_label->setText(tr("Effect evaluation system and emotion analysis of cross-screen homologous database"));
}
