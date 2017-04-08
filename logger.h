#ifndef LOGGER_H
#define LOGGER_H
#include <QDebug>

class Logger
{
public:
    enum class EMessageType: uint8_t
    {
        DEBUG,
        INFO,
        WARNING,
        CRITICAL,
        FATAL
    };

    Logger(EMessageType msgType, const char *fileName, const char* functionName, const int line, std::__cxx11::string a...);
};

#define LOG_DBG(a...)           LOG(Logger::EMessageType::DEBUG, a)
#define LOG_INFO(a...)          LOG(Logger::EMessageType::INFO, a)
#define LOG_WARNING(a...)       LOG(Logger::EMessageType::WARNING, a)
#define LOG_CRITICAL(a...)      LOG(Logger::EMessageType::CRITICAL, a)
#define LOG_FATAL(a...)         LOG(Logger::EMessageType::FATAL, a)

#define LOG(msgType, a,...)  Logger(msgType, __FILE__, __FUNCTION__, __LINE__, a)

#endif // LOGGER_H
