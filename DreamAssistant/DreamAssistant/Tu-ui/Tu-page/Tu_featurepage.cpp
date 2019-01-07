#include "Tu_featurepage.h"

FeaturePage::FeaturePage(QWidget *parent)
	: QWidget(parent)
{
	setFixedSize(900, 403);
	setAutoFillBackground(true);

	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(Qt::white));
	setPalette(palette);
}

FeaturePage::~FeaturePage()
{

}
