#ifndef TU_UPGRADEDIALOG_H
#define TU_UPGRADEDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>

#include "../Tu-utils/Tu_utils.h"
#include "../Tu-common/Tu_pushbutton.h"
#include "../Tu-common/Tu_loadinglabel.h"
#include "../Tu-component/Tu_basedialog.h"

class UpgradeDialog : public BaseDialog
{
	Q_OBJECT
public:
	explicit UpgradeDialog(QWidget *parent = Q_NULLPTR, const QString &version = "", QString skin = DEFAULT_SKIN);
	~UpgradeDialog();

	void resetTitleSkin(QString skin);
	void checkLastestVersion();

	void showErrorComponents();
	void showUpdateSourceComponents();

signals:
	void sig_close();
	void sig_showBackendBtn(bool flag);

public slots:
	void onCloseBtnClicked();
	void onUpgradeBtnClicked();
	void onRetryBtnClicked();
	void openUrl(QString url);

protected:
	void initUi();
	void initConnect();
	void setLanuage();

private:
	QWidget *baseWidget;
	PushButton *close_btn;
	QProgressBar *progressbar;

	QLabel *visit_label;
	QLabel *net_icon_label;
	QLabel *normal_icon_label;
	QLabel *ok_icon_label;

	LoadingLabel *work_loading_label;
	LoadingLabel *upgrade_loading_label;

	QLabel *nameLabel;
	QLabel *doing_label;
	QLabel *error_label;
	QLabel *tip_label;
	QLabel *splitlabel;
	QLabel *version_label;

	QWidget *new_widget;

	QLabel *hook_label;
	QLabel *official_label;
	QLabel *vline;
	QLabel *new_label;
	QLabel *new_num_label;

	QPushButton *retryBtn;
	QPushButton *upgradeBtn;
	QPushButton *okBtn;

	bool isBusy;
	bool upgradeOver;

	QString cur_version;
	QString cur_skin;
};

#endif // TU_UPGRADEDIALOG_H
