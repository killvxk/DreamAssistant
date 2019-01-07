#ifndef TU_TITLEWIDGET_H
#define TU_TITLEWIDGET_H

#include <QWidget>

#include "../Tu-common/Tu_pushbutton.h"

class TitleWidget : public QWidget
{
	Q_OBJECT
public:
	explicit TitleWidget(QWidget *parent = Q_NULLPTR);
	~TitleWidget();

signals:
	void sig_showMinimized();
	void sig_showMainMenu();
	void sig_showSkinCenter();
	void sig_closeApp();

protected:
	void initUi();
	void initLayout();
	void initConnect();

private:
	PushButton *min_button;
	PushButton *close_button;
	PushButton *skin_button;
	PushButton *main_menu_button;
};

#endif // TU_TITLEWIDGET_H
