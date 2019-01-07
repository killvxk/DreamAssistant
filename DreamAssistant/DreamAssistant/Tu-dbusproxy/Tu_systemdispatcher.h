#ifndef TU_SYSTEMDISPATCHER_H
#define TU_SYSTEMDISPATCHER_H

#include <QObject>

#include "Tu-business/Tu_businessinterface.h"

class SystemDispatcher : public QObject
{
	Q_OBJECT
public:
	explicit SystemDispatcher(QObject *parent = Q_NULLPTR);
	~SystemDispatcher();

	bool copy_file(QString filename);
	bool delete_file(QString filename);

private:
	BusinessInterface *businessInterface;
};

#endif // TU_SYSTEMDISPATCHER_H
