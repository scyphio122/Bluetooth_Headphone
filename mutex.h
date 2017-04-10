#ifndef MUTEX_H
#define MUTEX_H

#include <QMutex>

class CMutex
{
public:
    CMutex(QMutex* mutex);
    ~CMutex();

private:
    QMutex* m_mutex;
};



#endif // MUTEX_H
