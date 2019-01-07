#ifndef TU_ABOUTDIALOG_H
#define TU_ABOUTDIALOG_H

#include <QLabel>
#include <QTextBrowser>
#include <QParallelAnimationGroup>

#include "../Tu-utils/Tu_utils.h"
#include "../Tu-common/Tu_pushbutton.h"
#include "../Tu-component/Tu_basedialog.h"

class AboutDialog : public BaseDialog
{
	Q_OBJECT
public:
	explicit AboutDialog(QWidget *parent = Q_NULLPTR, const QString &version = "", QString skin = DEFAULT_SKIN);
	~AboutDialog();

	void resetTitleSkin(QString skin);

public slots:
	void onAboutBtnClicked();
	void onContributorBtnClicked();

protected:
	void initUi();
	void initAnimation();
	void initConnect();
	void setLanguage();

private:
	QWidget *baseWidget;
	PushButton *close_btn;
	QPushButton *aboutBtn;
	QPushButton *contributorBtn;
	QLabel *indicator;

	QTextBrowser *aboutEdit;
	QTextEdit *contributorEdit;

	QLabel *iconLabel;
	QLabel *nameLabel;
	QPushButton *okBtn;

	QParallelAnimationGroup *aboutGroup;
	QParallelAnimationGroup *contributorGroup;

	QString version;
	QString cur_skin;
};

#endif // TU_ABOUTDIALOG_H
