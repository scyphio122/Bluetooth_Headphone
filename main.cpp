#include <QCoreApplication>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#include <QDebug>
#include <cstdio>
#include "bluetoothscanner.h"
#include "logger.h"


//void errorHandler(QtMsgType type ,const QMessageLogContext& c, const QString& msg)
//{
//    (void) c;

//    const char* _msg = msg.toStdString().c_str();
//    switch (type)
//    {
//        case QtInfoMsg:
//            fprintf(stderr, "\e[94mInfo: %s\n\e[0m", _msg);
//            break;
//        case QtDebugMsg:
//            fprintf(stderr, "\e[92m%s\n", _msg);
//            break;
//        case QtWarningMsg:
//            fprintf(stderr, "\e[93mWarning: %s\n\e[0m", _msg);
//            break;
//        case QtCriticalMsg:
//            fprintf(stderr, "\e[31mCritical: %s\n\e[0m", _msg);
//            break;
//        case QtFatalMsg:
//            fprintf(stderr, "\e[31mFatal: %s\n\e[0m", _msg);
//            abort();
//    }
//}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CBluetoothScanner::GetInstance();

    LOG_INFO("INFO");
    LOG_DBG("DEBUG");
    LOG_WARNING("WARNING");
    LOG_CRITICAL("CRITICAL");

    return a.exec();
}
