#ifndef TU_EVALUATIONACTIONWIDGET_H
#define TU_EVALUATIONACTIONWIDGET_H

#include <QWidget>
#include <QLabel>

class EvaluationActionWidget : public QWidget
{
	Q_OBJECT
public:
	explicit EvaluationActionWidget(QWidget *parent = Q_NULLPTR);
	~EvaluationActionWidget();

protected:
	void initUi();
	void initLayout();
	void setLanguage();

private:
	QLabel *img_label;
	QLabel *title_label;
};

#endif // TU_EVALUATIONACTIONWIDGET_H
