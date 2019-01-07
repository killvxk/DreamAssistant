#include "Tu_cardwidget.h"

CardWidget::CardWidget(int cardwidth, int cardheight, int space, QWidget *parent)
	: QWidget(parent)
{
	cardcount = 0;
	number_per_row = -1;

	this->itemwidth = cardwidth;
	this->itemheight = cardheight;
	this->cardspace = space;

	scrollArea = new QScrollArea(this);
	scrollArea->setStyleSheet("QScrollArea{border: none;background-color: #ffffff;}");

	cardPanel = new QWidget();
	cardPanel->setStyleSheet("QWidget{border: none;background-color: #ffffff;}");

	this->scrollArea->setWidget(this->cardPanel);
	this->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	this->scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{margin:0px 0px 0px 0px;background-color:rgb(255,255,255,100);border:0px;width:6px;}\
														  QScrollBar::sub-line:vertical{subcontrol-origin:margin;border:1px solid red;height:13px}\
														  QScrollBar::up-arrow:vertical{subcontrol-origin:margin;background-color:blue;height:13px}\
														  QScrollBar::sub-page:vertical{background-color:#EEEDF0;}\
														  QScrollBar::handle:vertical{background-color:#D1D0D2;width:6px;} \
														  QScrollBar::handle:vertical:hover{background-color:#14ACF5;width:6px;} \
														  QScrollBar::handle:vertical:pressed{background-color:#0B95D7;width:6px;}\
                                                          QScrollBar::add-page:vertical{background-color:#EEEDF0;}\
														  QScrollBar::down-arrow:vertical{background-color:yellow;}\
														  QScrollBar::add-line:vertical{subcontrol-origin:margin;border:1px solid green;height:13px}");
}

CardWidget::~CardWidget()
{
	if (cardPanel != NULL)  {
		delete cardPanel;
		cardPanel = NULL;
	}
}

void CardWidget::calculate_data()
{
	this->scrollArea->setGeometry(0, 0, this->width(), this->height());
	this->cardPanel->setGeometry(0, 0, this->width(), this->height());

	this->number_per_row = (this->width() + this->cardspace) / (this->itemwidth + this->cardspace);
}

void CardWidget::add_card(QWidget *card)
{
	int x = int(this->cardcount % this->number_per_row) * (this->itemwidth + this->cardspace);
	int y = int(this->cardcount / this->number_per_row) * (this->itemheight + this->cardspace);

	int nowHeight = y + this->itemheight;

	if (nowHeight >= this->cardPanel->height())
		this->cardPanel->resize(this->cardPanel->width(), nowHeight);

	card->move(x, y);
	this->cardcount += 1;
}

void CardWidget::clear_card()
{
	foreach(QObject *child, this->cardPanel->children())
	{
		QWidget *widget = static_cast<QWidget *>(child);
		widget->deleteLater();
	}

	this->cardPanel->setGeometry(0, 0, this->width(), this->height());
	this->cardcount = 0;
}

