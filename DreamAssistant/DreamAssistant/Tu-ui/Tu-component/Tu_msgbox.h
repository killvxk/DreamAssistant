#ifndef TU_MSGBOX_H
#define TU_MSGBOX_H

#include <QLabel>

#include "Tu_basedialog.h"
#include "../Tu-utils/Tu_utils.h"
#include "../Tu-common/Tu_pushbutton.h"

class MsgBox : public BaseDialog
{
	Q_OBJECT
public:
	explicit MsgBox(QWidget *parent = Q_NULLPTR, QString skin = DEFAULT_SKIN);
	~MsgBox();

	void setInfo(QString title_info, QString info, QPixmap pixmap, bool is_ok_hidden);

signals:
	void sig_okMessageHidden(bool is_checked);
	void sig_msgChecked(bool is_checked, bool is_ok);

protected:
    void initUi();
    void initConnect();

private slots:
	void okOperate();
	void cancelOperate();

private:
	QLabel *title_label;
	QLabel *title_icon_label;
	QLabel *msg_label;
	QLabel *ask_label;

	PushButton *close_button;
	QPushButton *ok_button;
	QPushButton *cancel_button;

	QWidget *baseWidget;
};

#endif // TU_MSGBOX_H
