#ifndef TU_SKINDIALOG_H
#define TU_SKINDIALOG_H

#include <QSettings>

#include "../Tu-utils/Tu_utils.h"
#include "../Tu-common/Tu_pushbutton.h"
#include "../Tu-common/Tu_itemcard.h"
#include "../Tu-component/Tu_cardwidget.h"
#include "../Tu-component/Tu_basedialog.h"

class SystemDispatcher;
class QParallelAnimationGroup;

class SkinDialog : public BaseDialog
{
	Q_OBJECT
public:
	explicit SkinDialog(QWidget *parent = Q_NULLPTR, QSettings *settings = NULL, QString skin = DEFAULT_SKIN);
	~SkinDialog();

	void setSystemDbusProxy(SystemDispatcher* dispatcher) { systemProxy = dispatcher; }

	void initSysBackgroundList();
	void reloadBackgroundList();

signals:
	void sig_changeSkin(QString pciture);
	void sig_restoreSkin();

	void sig_reViewThePointSkin(QString pciture);
	void sig_reViewTheOrgSkin();

public slots:
	void changeSkinCenterBackground(QString pciture);
	void changeEnterBackground(QString pciture);
	void changeLeaveBackground();
	void deleteBackground(QString picture);
	void switchUsingLogo(QString index);
	void switchCusteomUsingLogo(QString index);
	void showSystem();
	void showCustom();
	void addCustomBackground();

protected:
	void initUi();
	void initAnimation();
	void initConnect();
	void setLanguage();

	QString getCurrentBackgroundName();
	QString getCurrentBackgroundAbsName();

protected:
	void closeEvent(QCloseEvent *event);

private:
	QWidget *baseWidget;
	PushButton *close_btn;

	QLabel *indicator;
	QLabel *label;

	QWidget *skin_widget;
	QString last_skin_path;

	QPushButton *sysBtn;
	QPushButton *customBtn;

	CardWidget *list_widget;
	QList<ItemCard *> card_list;

	CardWidget *custom_list_widget;
	QList<ItemCard *> custom_card_list;

	QSettings *mSettings;

	SystemDispatcher *systemProxy;

	QParallelAnimationGroup *aboutGroup;
	QParallelAnimationGroup *contributorGroup;
};

#endif // TU_SKINDIALOG_H
