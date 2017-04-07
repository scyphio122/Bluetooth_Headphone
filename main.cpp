#include <QCoreApplication>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>


#include "bluetoothscanner.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CBluetoothScanner::GetInstance();

    return a.exec();
}
