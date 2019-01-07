#ifndef TU_MAINMENU_H
#define TU_MAINMENU_H

#include <QMenu>
#include <QLabel>
#include <QPushButton>
#include <QWidgetAction>

class MainMenu : public QMenu
{
	Q_OBJECT
public:
	explicit MainMenu(QWidget *parent = Q_NULLPTR);
	~MainMenu();

signals:
	void sig_showUpgradePage();
	void sig_aboutUs();

public slots:
	void forumHelp();
	void questionFeedback();

private:
	void initActions();
	void initLayout();
	void initConnect();

	void setLanguage();

private:
	QWidget *check_widget;
	QWidget *help_widget;
	QWidget *feedback_widget;
	QWidget *about_widget;

	QWidgetAction *check_widget_action;
	QWidgetAction *help_widget_action;
	QWidgetAction *feedback_widget_action;
	QWidgetAction *about_widget_action;

	QLabel *check_label;
	QLabel *help_label;
	QLabel *feedback_label;
	QLabel *about_label;

	QPushButton *check_button;
	QPushButton *help_button;
	QPushButton *feedback_button;
	QPushButton *about_button;
};

#endif // TU_MAINMENU_H
