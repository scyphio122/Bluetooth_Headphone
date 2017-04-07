#include "logger.h"
#include <QTime>

Logger::Logger(const char* functionName, std::string a...)
{
    QString s;
    QTime curTime = QTime::currentTime();
    s = curTime.toString() + "." + QString::number(curTime.msec()) + ": " + QString(functionName) + " <<< " + QString::fromStdString(a);
    qDebug(s.toStdString().c_str());
}
