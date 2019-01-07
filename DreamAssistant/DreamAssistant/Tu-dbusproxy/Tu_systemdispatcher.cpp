#include "Tu_systemdispatcher.h"

SystemDispatcher::SystemDispatcher(QObject *parent)
	: QObject(parent)
{
	businessInterface = new BusinessInterface(this);
}

SystemDispatcher::~SystemDispatcher()
{

}

bool SystemDispatcher::copy_file(QString filename)
{
	return businessInterface->copy_file(filename);
}

bool SystemDispatcher::delete_file(QString filename)
{
	return businessInterface->delete_file(filename);
}
