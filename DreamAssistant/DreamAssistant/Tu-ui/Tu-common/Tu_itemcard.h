#ifndef TU_ITEMCARD_H
#define TU_ITEMCARD_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>

class ItemCard : public QWidget
{
	Q_OBJECT
public:
	explicit ItemCard(QString title = "", bool flag = false, QWidget *parent = Q_NULLPTR);
	~ItemCard();

	void showUsingLogo(bool flag);
	void resetdislayDelBtnValue(bool flag);
	QString getCardName();

public slots:
	void onDeleteBtnClicked();

signals:
	void sig_backgroundName(QString name);
	void sig_enterBackgroundSkin(QString name);
	void sig_leaveBackgroundSkin();
	void sig_delteSkin(QString name);
	void sig_addSkin();

protected:
	void initUi();

protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	bool eventFilter(QObject *obj, QEvent *event);

private:
	bool showDelay;
	bool dislayDelBtn;

	QString switchDirection;
	int py;

	QString iconDir;
	QString iconpath;

	QWidget  *baseWidget;
	QWidget  *coverWidget;
	QWidget  *deleteWidget;

	QLabel   *icon;
	QLabel   *using_label;
	QLabel   *name;

	QPushButton *deleteBtn;
};

#endif // TU_ITEMCARD_H
