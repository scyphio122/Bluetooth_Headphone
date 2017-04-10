#ifndef BLUETOOTHDEVICE_H
#define BLUETOOTHDEVICE_H
#include <string>
#include <QString>
#include <bluetooth/bluetooth.h>

class CBluetoothDevice
{
public:
    CBluetoothDevice(bdaddr_t *macAddr, const char* devName = nullptr, uint8_t devClass[3] = nullptr);

    CBluetoothDevice(const char* macAddr, const char* devName = nullptr, uint8_t devClass[3] = nullptr);

    ~CBluetoothDevice();

    bdaddr_t GetMac();

    std::string GetMacString();

    QString GetMacQString();

    std::string GetDeviceName();

    void SetDeviceName(const char* name);

    void SetDeviceClass(uint8_t devClass[]);

    int GetDeviceClass();

private:
    bdaddr_t m_macAddress;

    std::string m_devName;

    uint8_t m_deviceClass[3];

};

#endif // BLUETOOTHDEVICE_H
