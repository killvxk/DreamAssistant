#ifndef TU_MAPBUTTON_H
#define TU_MAPBUTTON_H

#include <QLabel>

#include "../Tu-utils/Tu_utils.h"

class MapButton : public QWidget
{
	Q_OBJECT
public:
	explicit MapButton(QWidget *parent = 0, bool whiteflag = false);
	~MapButton();

	void setIcon(const QString &icon);
	void setText(const QString &text);
	void setMapButtonStatus(BUTTONSTATUS status);

signals:
	void clicked();

protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);

	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);

private:
	QLabel *iconLabel;
	QLabel *textLabel;
};

#endif // TU_MAPBUTTON_H
