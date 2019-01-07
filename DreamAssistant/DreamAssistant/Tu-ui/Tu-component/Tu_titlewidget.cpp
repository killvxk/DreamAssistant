#include "Tu_titlewidget.h"
#include <QHBoxLayout>

TitleWidget::TitleWidget(QWidget *parent)
	: QWidget(parent)
{
	setFixedSize(900, 36);

	initUi();
	initLayout();
	initConnect();
}

TitleWidget::~TitleWidget()
{

}

void TitleWidget::initUi()
{
	min_button = new PushButton;
	close_button = new PushButton;
	skin_button = new PushButton;
	main_menu_button = new PushButton;

	min_button->loadPixmap(":/res/title/min_button.png");
	close_button->loadPixmap(":/res/title/close_button.png");
	skin_button->loadPixmap(":/res/title/skin_button.png");
	main_menu_button->loadPixmap(":/res/title/main_menu.png");

	min_button->setFocusPolicy(Qt::NoFocus);
	close_button->setFocusPolicy(Qt::NoFocus);
	skin_button->setFocusPolicy(Qt::NoFocus);
	main_menu_button->setFocusPolicy(Qt::NoFocus);
}

void TitleWidget::initLayout()
{
	QHBoxLayout *main_layout = new QHBoxLayout();

	main_layout->addWidget(close_button, 0, Qt::AlignTop);
	main_layout->addWidget(min_button, 0, Qt::AlignTop);
	main_layout->addWidget(skin_button, 0, Qt::AlignTop);
	main_layout->addWidget(main_menu_button, 0, Qt::AlignTop);
	main_layout->addStretch();
	main_layout->setSpacing(0);
	main_layout->setContentsMargins(0, 0, 0, 0);

	setLayout(main_layout);
}

void TitleWidget::initConnect()
{
	connect(min_button, &PushButton::clicked, this, &TitleWidget::sig_showMinimized);
	connect(main_menu_button, &PushButton::clicked, this, &TitleWidget::sig_showMainMenu);
	connect(skin_button, &PushButton::clicked, this, &TitleWidget::sig_showSkinCenter);
	connect(close_button, &PushButton::clicked, this, &TitleWidget::sig_closeApp);
}
