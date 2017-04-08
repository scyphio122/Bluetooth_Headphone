#include "logger.h"
#include <QTime>

Logger::Logger(EMessageType msgType, const char* functionName, std::string a...)
{
    QString s;
    switch(msgType)
    {
        case EMessageType::INFO:
            s = "\e[94mINFO: ";
            break;
        case EMessageType::DEBUG:
            s = "\e[92mDBG: ";
            break;

        case EMessageType::WARNING:
            s = "\e[93mWARNING: ";
            break;
        case EMessageType::CRITICAL:
            s = "\e[31mCRITICAL: ";
            break;
        case EMessageType::FATAL:
            s = "\e[31mFatal: ";
            break;
    }

    QTime curTime = QTime::currentTime();
    s += curTime.toString() + "." + QString::number(curTime.msec()) + ": " + QString(functionName) + " <<< " + QString::fromStdString(a);
    s += "\e[0m";

    switch(msgType)
    {
        case EMessageType::INFO:
            qInfo(s.toStdString().c_str());
            break;
        case EMessageType::DEBUG:
            qDebug(s.toStdString().c_str());
            break;

        case EMessageType::WARNING:
            qWarning(s.toStdString().c_str());
            break;
        case EMessageType::CRITICAL:
            qCritical(s.toStdString().c_str());
            break;
        case EMessageType::FATAL:
            qFatal(s.toStdString().c_str());
            break;
    }
}
