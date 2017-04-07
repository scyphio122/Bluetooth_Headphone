#ifndef LOGGER_H
#define LOGGER_H
#include <QDebug>

class Logger
{
public:
    Logger(const char* functionName, std::__cxx11::string a...);
};

#define LOG(a,...)  Logger(__FUNCTION__, a)

#endif // LOGGER_H
