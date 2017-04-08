#ifndef BLUETOOTHDEVICE_H
#define BLUETOOTHDEVICE_H
#include <string>
#include <QString>
#include <bluetooth/bluetooth.h>

class CBluetoothDevice
{
public:
    CBluetoothDevice(bdaddr_t *macAddr);

    CBluetoothDevice(const char* macAddr);

    ~CBluetoothDevice();

    bdaddr_t GetMac();

    std::string GetMacString();

    QString GetMacQString();


private:
    bdaddr_t m_macAddress;
};

#endif // BLUETOOTHDEVICE_H
