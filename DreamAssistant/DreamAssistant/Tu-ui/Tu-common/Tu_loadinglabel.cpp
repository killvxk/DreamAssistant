#include "Tu_loadinglabel.h"
#include <QBitmap>

LoadingLabel::LoadingLabel(QWidget *parent, QString flag)
	: QLabel(parent)
	, category(flag)
{
	if (category == "firstkey") {
		page_count = 18;
		this->setFixedSize(150, 150);
	} else if (category == "clean") {
		page_count = 18;
		this->setFixedSize(96, 96);
	}else if (category == "upgrading") {
		page_count = 32;
		setFixedSize(182, 181);
	} else if (category == "working") {
		page_count = 36;
		setFixedSize(182, 181);
	}

	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground, true);

	currentpage = 0;

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(changeAnimationStep()));

	this->loadAllPictures();

	//init animation
	QPixmap cur_pix = png_vector.at(0);
	this->setPixmap(cur_pix);
	setMask(QBitmap(cur_pix.mask()));
}

LoadingLabel::~LoadingLabel()
{
	if (timer != NULL) {
		disconnect(timer, SIGNAL(timeout()), this, SLOT(changeAnimationStep()));
		if (timer->isActive()) {
			timer->stop();
		}
		delete timer;
		timer = NULL;
	}
}

void LoadingLabel::changeAnimationStep()
{
	if (currentpage == page_count) {
		currentpage = 0;
	}

	QPixmap cur_pix = png_vector.at(currentpage);
	this->setPixmap(cur_pix);
	setMask(QBitmap(cur_pix.mask()));

	currentpage += 1;
}

void LoadingLabel::loadAllPictures()
{
	QString path;
	if (category == "firstkey") {
		path = ":/res/home/loading/";
	} else if (category == "clean") {
		path = ":/res/home/loading/small/";
	} else if (category == "upgrading") {
		path = ":/res/upgrade/upgrading/";
	} else if (category == "working") {
		path = ":/res/upgrade/working/";
	}

	for (int i = 1; i <= page_count; i++) {
		QPixmap img = QPixmap(path + QString::number(i, 10) + ".png");
		png_vector.append(img);
	}
}

void LoadingLabel::startLoading()
{
	currentpage = 0;
	if (category == "upgrading" || category == "working")
		timer->start(50);
	else
		timer->start(60);
}

void LoadingLabel::stopLoading()
{
	timer->stop();
}
