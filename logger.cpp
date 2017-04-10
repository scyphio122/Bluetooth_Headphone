#include "logger.h"
#include <QTime>

#include <cstdio>
#include <cstdarg>

std::map<int, std::string> Logger::s_errnoMap = {
               {    0,           "No error"},
               {	EPERM,		 "Operation not permitted"},
               {	ENOENT,		 "No such file or directory"},
               {	ESRCH,		 "No such process!"},
               {	EINTR,		 "Interrupted system call"},
               {	EIO,		 "I/O error"},
               {	ENXIO,		 "No such device or address"},
               {	E2BIG,		 "Argument list too long"},
               {	ENOEXEC,	 "Exec format error"},
               {   EBADF,		 "Bad file number"},
               {   ECHILD,       "No child processes"},
               {   EAGAIN,       "Try again"},
               {   ENOMEM,       "Out of memory"},
               {   EACCES,       "Permission denied"},
               {   EFAULT,       "Bad address"},
               {   ENOTBLK,	     "Block device required"},
               {   EBUSY,		 "Device or resource busy"},
               {   EEXIST,	     "File exists"},
               {	EXDEV,		 "Cross-device link"},
               {	ENODEV,		 "No such device"},
               {	ENOTDIR,	 "Not a directory"},
               {	EISDIR,		 "Is a directory"},
               {	EINVAL,		 "Invalid argument"},
               {	ENFILE,		 "File table overflow"},
               {	EMFILE,		 "Too many open files"},
               {	ENOTTY,		 "Not a typewriter"},
               {	ETXTBSY,	 "Text file busy"},
               {	EFBIG,		 "File too large"},
               {	ENOSPC,		 "No space left on device"},
               {	ESPIPE,		 "Illegal seek"},
               {	EROFS,		 "Read-only file system"},
               {	EMLINK,		 "Too many links"},
               {	EPIPE,		 "Broken pipe"},
            #ifdef EDOM
               {	EDOM,		 "Math argument out of domain of func"},
            #endif
            #ifdef ERANGE
               {	ERANGE,		 "Math result not representable"}
            #endif
           };



Logger::Logger(EMessageType msgType, const char* fileName, const char* functionName, const int line, const char* a, ...)
{
    QString s;
    char msg[M_LOG_BUFFER_SIZE] = {0};

    va_list args;
    va_start(args, a);
    std::vsprintf(msg, a, args);
    va_end(args);

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
    s += curTime.toString() + "." + QString::number(curTime.msec()) + " " + QString(fileName) + " <<< " + QString(functionName) + ":" + QString::number(line) + " ### " + QString::fromStdString(msg);
    s += "\e[0m";

    std::printf("%s\n", s.toStdString().c_str());

}
