#include "mutex.h"
#include <QMutex>

CMutex::CMutex(QMutex *mutex)
{
    m_mutex = mutex;
    m_mutex->lock();
}

CMutex::~CMutex()
{
    m_mutex->unlock();
}
