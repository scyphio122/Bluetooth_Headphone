#include "bluetoothdevice.h"
#include <cstdlib>
#include <bluetooth/bluetooth.h>

CBluetoothDevice::CBluetoothDevice(bdaddr_t* macAddr)
{
    memcpy(macAddr, &m_macAddress, sizeof(bdaddr_t));
}

CBluetoothDevice::CBluetoothDevice(const char *macAddr)
{
    str2ba(macAddr, &m_macAddress);
}

CBluetoothDevice::~CBluetoothDevice()
{

}


bdaddr_t CBluetoothDevice::GetMac()
{
    return m_macAddress;
}

std::string CBluetoothDevice::GetMacString()
{
    char addr[] = "xx-xx-xx-xx-xx-xx";
    ba2str(&m_macAddress, addr);

    return std::string(addr);
}

QString CBluetoothDevice::GetMacQString()
{
    return QString::fromStdString(GetMacString());
}
