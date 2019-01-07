#ifndef TU_FEATUREACTIONWIDGET_H
#define TU_FEATUREACTIONWIDGET_H

#include <QLabel>

class FeatureActionWidget : public QWidget
{
	Q_OBJECT
public:
	explicit FeatureActionWidget(QWidget *parent = Q_NULLPTR);
	~FeatureActionWidget();

protected:
	void initUi();
	void initLayout();
	void setLanguage();

private:
	QLabel *img_label;
	QLabel *title_label;
};

#endif // TU_FEATUREACTIONWIDGET_H
