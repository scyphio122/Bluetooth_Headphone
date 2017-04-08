#include "logger.h"
#include <QTime>

Logger::Logger(EMessageType msgType, const char* fileName, const char* functionName, const int line, std::string a...)
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
    s += curTime.toString() + "." + QString::number(curTime.msec()) + " " + QString(fileName) + " <<< " + QString(functionName) + ":" + QString::number(line) + " ### " + QString::fromStdString(a);
    s += "\e[0m";

    qDebug(s.toStdString().c_str());
}
