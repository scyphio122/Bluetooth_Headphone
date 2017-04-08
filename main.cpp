#include <QCoreApplication>
#include "bluetoothscanner.h"
#include "logger.h"


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
