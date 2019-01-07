#ifndef TU_CARDWIDGET_H
#define TU_CARDWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>

class CardWidget : public QWidget
{
	Q_OBJECT
public:
	explicit CardWidget(int cardwidth = 0, int cardheight = 0, int space = 0, QWidget *parent = Q_NULLPTR);
	~CardWidget();

	void calculate_data();
	void add_card(QWidget *card);
	void clear_card();

	QWidget *cardPanel;

private:
	int cardcount;
	int number_per_row;
	int itemwidth;
	int itemheight;
	int cardspace;

	QScrollArea *scrollArea;	
};

#endif // TU_CARDWIDGET_H
