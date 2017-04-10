#ifndef LOGGER_H
#define LOGGER_H
#include <QDebug>
#include <errno.h>
#include <map>

#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)

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

    static std::map<int, std::string> s_errnoMap;

    Logger(EMessageType msgType, const char *fileName, const char* functionName, const int line, const char *a, ...);

private:
    const unsigned short M_LOG_BUFFER_SIZE = 512;

};

#define LOG_ERRNO() LOG_CRITICAL("ERRNO MESSAGE: %s", Logger::s_errnoMap[errno].c_str())

#define LOG_DBG(...)           LOG(Logger::EMessageType::DEBUG, __VA_ARGS__ )
#define LOG_INFO(...)          LOG(Logger::EMessageType::INFO, __VA_ARGS__)
#define LOG_WARNING(...)       LOG(Logger::EMessageType::WARNING, __VA_ARGS__ )
#define LOG_CRITICAL(...)      LOG(Logger::EMessageType::CRITICAL, __VA_ARGS__ )
#define LOG_FATAL(...)         LOG(Logger::EMessageType::FATAL, __VA_ARGS__ )

#define LOG(msgType, ...)  Logger(msgType, __FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__ )

#endif // LOGGER_H
