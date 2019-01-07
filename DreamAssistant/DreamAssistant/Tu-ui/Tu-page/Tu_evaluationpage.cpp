#include "Tu_evaluationpage.h"

EvaluationPage::EvaluationPage(QWidget *parent)
	: QWidget(parent)
{
	setFixedSize(900, 403);
	setAutoFillBackground(true);

	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(Qt::white));
	setPalette(palette);
}

EvaluationPage::~EvaluationPage()
{

}
