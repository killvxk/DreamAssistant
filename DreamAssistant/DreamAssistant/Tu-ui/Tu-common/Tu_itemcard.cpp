#include "Tu_itemcard.h"
#include <QCoreApplication>

ItemCard::ItemCard(QString title, bool flag, QWidget *parent)
	: QWidget(parent)
{
	setFixedSize(132, 87);

	dislayDelBtn = false;
	showDelay = false;	

	initUi();

	if (flag)
		iconDir = QCoreApplication::applicationDirPath().append("/skin/custom/");
	else
		iconDir = QCoreApplication::applicationDirPath().append("/skin/default/");

	if (title == ":/res/skin/create.png") {
		iconpath = title;
		name->hide();
		this->setCursor(Qt::PointingHandCursor);
	} else {
		iconpath = iconDir.append(title);
	}

	QPixmap pixmap(iconpath);
	pixmap.copy(QRect(0, 0, 130, 68));
	icon->setPixmap(pixmap);

	name->setText(title.replace(".png", "").replace(".jpg", ""));
}

ItemCard::~ItemCard()
{
	
}

void ItemCard::initUi()
{
	baseWidget = new QWidget(this);
	baseWidget->setGeometry(1, 1, 130, 67);
	baseWidget->setStyleSheet("QWidget{background:transparent;}");

	icon = new QLabel(baseWidget);
	icon->setGeometry(0, 0, 130, 67);
	icon->installEventFilter(this);

	using_label = new QLabel(baseWidget);
	using_label->setGeometry(104, 5, 22, 22);
	using_label->setStyleSheet("QLabel{background-image:url(':/res/skin/choose.png')}");
	using_label->hide();

	coverWidget = new QWidget(this);
	coverWidget->setGeometry(0, 0, 132, 69);
	coverWidget->lower();
	coverWidget->setStyleSheet("QWidget{background:transparent url(:/res/skin/skin-cover.png);}");
	coverWidget->hide();

	deleteWidget = new QWidget(this);
	deleteWidget->setGeometry(1, 50, 130, 18);
	deleteWidget->setStyleSheet("QWidget{background:transparent url(:/res/skin/conceal.png);}");
	deleteWidget->hide();

	deleteBtn = new QPushButton(deleteWidget);
	deleteBtn->setGeometry(3, 2, 16, 14);
	deleteBtn->setFocusPolicy(Qt::NoFocus);
	deleteBtn->setCursor(Qt::PointingHandCursor);
	deleteBtn->setStyleSheet("QPushButton{background-image:url(':/res/skin/remove.png');border:0px;}");

	name = new QLabel(this);
	name->setGeometry(5, 67, 122, 20);
	name->setStyleSheet("QLabel{background: transparent; font-size:13px;color:#666666;}");
	
	connect(deleteBtn, &QPushButton::clicked, this, &ItemCard::onDeleteBtnClicked);
}

void ItemCard::resetdislayDelBtnValue(bool flag)
{
	if (flag)
		this->dislayDelBtn = true;
	else
		this->dislayDelBtn = false;
}

void ItemCard::onDeleteBtnClicked()
{
	emit sig_delteSkin(iconpath);
}

void ItemCard::showUsingLogo(bool flag)
{
	if (flag)
		using_label->show();
	else
		using_label->hide();
}

QString ItemCard::getCardName()
{
	return this->iconpath;
}

void ItemCard::enterEvent(QEvent *)
{
	emit sig_enterBackgroundSkin(iconpath);

	if (this->iconpath != ":/res/skin/create.png")
		coverWidget->show();
	if (this->dislayDelBtn) {
		deleteWidget->show();
	}
}

void ItemCard::leaveEvent(QEvent *)
{
	emit sig_leaveBackgroundSkin();

	if (this->iconpath != ":/res/skin/create.png")
		coverWidget->hide();
	if (this->dislayDelBtn)
		deleteWidget->hide();
}

bool ItemCard::eventFilter(QObject *obj, QEvent *event)
{
	if (obj == icon){
		if (event->type() == QEvent::MouseButtonRelease){
			if (this->iconpath == ":/res/skin/create.png")
				emit sig_addSkin();
			else
				emit sig_backgroundName(iconpath);
		}
	}

	return QObject::eventFilter(obj, event);
}
