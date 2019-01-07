#ifndef TU_TOOLKITSACTIONWIDGET_H
#define TU_TOOLKITSACTIONWIDGET_H

#include <QLabel>
#include <QPushButton>

class ToolKitsActionWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ToolKitsActionWidget(QWidget *parent = Q_NULLPTR);
	~ToolKitsActionWidget();

protected:
	void initUi();
	void initLayout();
	void setLanguage();

private:
	QLabel *img_label;
	QLabel *title_label;

	QPushButton *more_btn;
};

#endif // TU_TOOLKITSACTIONWIDGET_H
