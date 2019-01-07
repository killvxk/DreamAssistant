#ifndef TU_LOADINGLABEL_H
#define TU_LOADINGLABEL_H

#include <QLabel>
#include <QTimer>

class LoadingLabel : public QLabel
{
	Q_OBJECT
public:
	explicit LoadingLabel(QWidget *parent = Q_NULLPTR, QString flag = "");
	~LoadingLabel();

	void loadAllPictures();
	void startLoading();
	void stopLoading();

public slots:
	void changeAnimationStep();

private:
	QTimer *timer;
	QVector<QPixmap> png_vector;

	int currentpage;
	int page_count;

	bool load_finished;

	QString category;
};

#endif // TU_LOADINGLABEL_H
