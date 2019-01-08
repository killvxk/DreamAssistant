#ifndef TU_SHREDDIALOG_H
#define TU_SHREDDIALOG_H

#include <QDialog>
#include <QSettings>

#include "../Tu-common/Tu_editbutton.h"
#include "../Tu-component/Tu_titlebar.h"
#include "../Tu-component/Tu_msgbox.h"

class QLineEdit;
class QPushButton;
class ShredFile;

class ShredDialog : public QDialog
{
	Q_OBJECT
public:
	explicit ShredDialog(ShredFile *plugin, QDialog *parent = Q_NULLPTR);
	~ShredDialog();

	void resetSkin();

public slots:
	void onSelectButtonClicked();
	void onShredButtonClicked();
	void onCacelButtonClicked();

protected:
	void initUi();
	void initLayout();
	void initConnect();
	void setLanguage();

	QString getCurrrentSkinName();

protected:
	void closeEvent(QCloseEvent *event);

private:
	ShredFile *process_plugin;

    TitleBar *title_bar;
    EditButton *select_btn;

	QLineEdit *select_edit;
	QPushButton *shred_btn;
	QPushButton *cacel_btn;

	QSettings *shred_settings;
};

#endif // TU_SHREDDIALOG_H
