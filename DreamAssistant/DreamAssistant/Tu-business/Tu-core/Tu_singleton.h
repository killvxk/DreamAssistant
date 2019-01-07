﻿#ifndef TU_SINGLETON_H
#define TU_SINGLETON_H

#include <QMutex>
#include <QScopedPointer>

template <typename T>
class Singleton {
public:
	static T& Instance();

	Singleton(const Singleton &other);
	Singleton<T>& operator=(const Singleton &other);

private:
	static QMutex mutex;
	static QScopedPointer<T> instance;
};

template <typename T> QMutex Singleton<T>::mutex;
template <typename T> QScopedPointer<T> Singleton<T>::instance;
template <typename T>
T& Singleton<T>::Instance()
{
	if (instance.isNull())
	{
		mutex.lock();
		if (instance.isNull()) {
			instance.reset(new T());
		}
		mutex.unlock();
	}
	return *instance.data();
}

#define SINGLETON(Class)                        \
private:                                        \
    Class();                                    \
    ~Class();                                   \
    Class(const Class &other);                  \
    Class& operator=(const Class &other);       \
    friend class Singleton<Class>;              \
    friend struct QScopedPointerDeleter<Class>; 

#endif // TU_SINGLETON_H