#include <QCoreApplication>
#include "bluetoothscanner.h"
#include "logger.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CBluetoothScanner* bluetoothScanner = CBluetoothScanner::GetInstance();

    bluetoothScanner->StartScanning();

    return a.exec();
}
