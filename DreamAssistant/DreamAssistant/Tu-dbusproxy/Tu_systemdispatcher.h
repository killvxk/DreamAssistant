#ifndef TU_SYSTEMDISPATCHER_H
#define TU_SYSTEMDISPATCHER_H

#include <QObject>

class SystemDispatcher : public QObject
{
	Q_OBJECT
public:
	explicit SystemDispatcher(QObject *parent = Q_NULLPTR);
	~SystemDispatcher();

	bool copy_file(QString filename);
	bool delete_file(QString filename);

private:

};

#endif // TU_SYSTEMDISPATCHER_H
