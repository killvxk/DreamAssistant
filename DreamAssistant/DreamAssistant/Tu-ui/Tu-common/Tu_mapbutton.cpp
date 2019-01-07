#include "Tu_mapbutton.h"
#include <QVBoxLayout>
#include <QFont>
#include <QFontMetrics>
#include <QMouseEvent>

MapButton::MapButton(QWidget *parent, bool whiteflag)
	: QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
	setAutoFillBackground(true);
	setCursor(Qt::PointingHandCursor);
	setFixedSize(90, 90);
	setFocusPolicy(Qt::NoFocus);

	QPalette palette;
	palette.setColor(this->backgroundRole(), QColor(255, 255, 255));
	setPalette(palette);

	iconLabel = new QLabel;
	textLabel = new QLabel;

	if (whiteflag)
		textLabel->setObjectName("backgroundWhiteLabel");
	else
		textLabel->setObjectName("backgroundLabel");

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(iconLabel, 0, Qt::AlignCenter);
	layout->addWidget(textLabel, 0, Qt::AlignHCenter);
	layout->setContentsMargins(8, 10, 8, 8);
	setLayout(layout);
}

MapButton::~MapButton()
{

}

void MapButton::setIcon(const QString &icon)
{
	QPixmap pixmap(icon);
	iconLabel->setPixmap(pixmap);
	iconLabel->setFixedSize(pixmap.size());
}

void MapButton::setText(const QString &text)
{
	QFont ft;
	QFontMetrics fm(ft);
	QString elided_text = fm.elidedText(text, Qt::ElideRight, 90);
	textLabel->setText(elided_text);
	textLabel->adjustSize();
	if (elided_text.endsWith(QStringLiteral("бн")))
		this->setToolTip(text);
}

void MapButton::setMapButtonStatus(BUTTONSTATUS status)
{
	QPalette palette;
	switch (status) {
	case BUTTON_ENTER:
		palette.setColor(this->backgroundRole(), QColor(233, 238, 241));//#e9eef1
		this->setPalette(palette);
		break;
	case BUTTON_LEAVE:
		palette.setColor(this->backgroundRole(), QColor(255, 255, 255));//#ffffff
		this->setPalette(palette);
		break;
	case BUTTON_PRESSED:
		palette.setColor(this->backgroundRole(), QColor(233, 238, 241));//#e9eef1
		this->setPalette(palette);
		break;
	default:
		break;
	}
}

void MapButton::enterEvent(QEvent *)
{
	setMapButtonStatus(BUTTON_ENTER);
}

void MapButton::leaveEvent(QEvent *)
{
	setMapButtonStatus(BUTTON_LEAVE);
}

void MapButton::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton) {
		MapButton(BUTTON_PRESSED);
	} else {
		e->ignore();
	}
}

void MapButton::mouseReleaseEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		if (rect().contains(e->pos()))
		{
			if (this->isEnabled()) {
				emit clicked();
			}
			setMapButtonStatus(BUTTON_ENTER);
			e->accept();
		} else {
			setMapButtonStatus(BUTTON_LEAVE);
			e->ignore();
		}
	} else {
		e->ignore();
	}
}
