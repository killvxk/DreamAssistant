#include "Tu_shreddialog.h"
#include "Tu_utils.h"
#include "../Tu-interface/Tu_filewipe.h"
#include "../Tu-interface/Tu_shredFile.h"
#include <QFileDialog>
#include <QDir>
#include <QIcon>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QCoreApplication>
#include <QCloseEvent>

ShredDialog::ShredDialog(ShredFile *plugin, QDialog *parent)
	: QDialog(parent)
	, process_plugin(plugin)
{
	setFixedSize(500, 300);
	setWindowFlags(Qt::FramelessWindowHint);
	setWindowIcon(QIcon(":/res/dream.png"));
	setStyleSheet("QDialog{border: 1px solid white;border-radius:1px;background-color: #ffffff;}");

	initUi();
	initLayout();
	initConnect();

	setLanguage();
}

ShredDialog::~ShredDialog()
{
	if (shred_settings != NULL) {
		shred_settings->sync();

		delete shred_settings;
		shred_settings = NULL;
	}
}

void ShredDialog::initUi()
{
	shred_settings = new QSettings(DREAM_COMPANY_SETTING, DREAM_SETTING_FILE_NAME_SETTING);
	shred_settings->setIniCodec("UTF-8");

	title_bar = new TitleBar;
	title_bar->setTitleWidth(500);
	title_bar->setTitleName(tr("Shred File"));
	title_bar->setTitleBackgound(getCurrrentSkinName());

	select_edit = new QLineEdit;
	select_edit->setStyleSheet("QLineEdit{border:1px solid #bebebe; color:#aaa; font-family: ·½ÕýºÚÌå_GBK;font-size: 12px;}");
	select_edit->setFixedWidth(400);
	select_edit->setReadOnly(true);

	select_btn = new EditButton(select_edit);

	shred_btn = new QPushButton;
	shred_btn->setFixedSize(91, 25);
	shred_btn->setObjectName("blackButton");
	shred_btn->setFocusPolicy(Qt::NoFocus);

	cacel_btn = new QPushButton;
	cacel_btn->setFixedSize(91, 25);
	cacel_btn->setObjectName("blackButton");
	cacel_btn->setFocusPolicy(Qt::NoFocus);
}

void ShredDialog::initLayout()
{
	QHBoxLayout *layout1 = new QHBoxLayout;
	layout1->addStretch();
	layout1->addWidget(select_edit);
	layout1->addStretch();

	QHBoxLayout *layout2 = new QHBoxLayout;
	layout2->addStretch();
	layout2->addWidget(shred_btn);
	layout2->addWidget(cacel_btn);
	layout2->addStretch();
	layout2->setMargin(0);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addStretch();
	layout->addLayout(layout1);
	layout->addLayout(layout2);
	layout->addStretch();
	layout->setSpacing(10);

	QVBoxLayout *main_layout = new QVBoxLayout;
	main_layout->addWidget(title_bar);
	main_layout->addLayout(layout);
	main_layout->setSpacing(20);
	main_layout->setMargin(0);
	main_layout->setContentsMargins(0, 0, 0, 0);
	setLayout(main_layout);
}

void ShredDialog::initConnect()
{
	connect(select_btn, &EditButton::clicked, this, &ShredDialog::onSelectButtonClicked);
	connect(shred_btn, &QPushButton::clicked, this, &ShredDialog::onShredButtonClicked);
	connect(cacel_btn, &QPushButton::clicked, this, &ShredDialog::onCacelButtonClicked);
	connect(title_bar, &TitleBar::sig_closeDialog, this, &ShredDialog::close);
}

void ShredDialog::setLanguage()
{
	setWindowTitle(tr("Shred File"));

	select_edit->setText(tr("No select any file which need to be shredded"));
	shred_btn->setText(tr("Shred File"));
	cacel_btn->setText(tr("Deselect"));
}

void ShredDialog::onSelectButtonClicked()
{
	QStringList fileNameList;
	QString fileName;

	QFileDialog* fd = new QFileDialog(this);
	fd->resize(500, 471);
//	fd->setFilter(tr("Allfile(*)"));
	fd->setViewMode(QFileDialog::List); 

	if (fd->exec() == QDialog::Accepted) {
		fileNameList = fd->selectedFiles();
		fileName = fileNameList[0];
		select_edit->setText(fileName);
	} else {
		fd->close();
	}
}

void ShredDialog::onShredButtonClicked()
{
    MsgBox *msg_box = new MsgBox(NULL, getCurrrentSkinName());

	if (select_edit->text().length() == 0 || !select_edit->text().contains("/")) {
        msg_box->setInfo(tr("Shred File"), QObject::tr("Please select a file!"), QPixmap(":/res/attention.png"), true);
	} else {
		QByteArray ba = select_edit->text().toUtf8();
		QStringList list;
		list << ba.data();
		bool result = FileWipe::Instance()->startWipeFile(list);
		if (result) {
			// success
            msg_box->setInfo(tr("Shred File"), QObject::tr("Shred successfully!"), QPixmap(":/res/attention.png"), true);
			select_edit->setText(tr("No select any file which need to be shredded"));
		} else {
			// failed
            msg_box->setInfo(tr("Shred File"), QObject::tr("Shred failed!"), QPixmap(":/res/attention.png"), true);
		}
	}
    msg_box->show();
    msg_box->exec();
}

void ShredDialog::onCacelButtonClicked()
{
	select_edit->setText(tr("No select any file which need to be shredded"));
}

void ShredDialog::resetSkin()
{
	QString skin = getCurrrentSkinName();
	title_bar->resetBackground(skin);
}

QString ShredDialog::getCurrrentSkinName()
{
	shred_settings->beginGroup("Background");
	QString skin = shred_settings->value("Path").toString();
	shred_settings->endGroup();
	shred_settings->sync();

	if (skin.isEmpty()) {
		skin = DEFAULT_SKIN;
	}

	return skin;
}

void ShredDialog::closeEvent(QCloseEvent *event)
{
	event->accept();
}
