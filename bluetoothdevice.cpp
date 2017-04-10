#include "bluetoothdevice.h"
#include <cstdlib>
#include <bluetooth/bluetooth.h>

CBluetoothDevice::CBluetoothDevice(bdaddr_t* macAddr, const char *devName, uint8_t devClass[3])
{
    memcpy(macAddr, &m_macAddress, sizeof(bdaddr_t));
    if(devName != nullptr)
        m_devName = std::string(devName);

    if(!devClass)
    {
        for(int i=0; i<3;++i)
            m_deviceClass[i] = -1;
    }
    else
        memcpy(m_deviceClass, devClass, 3);
}

CBluetoothDevice::CBluetoothDevice(const char *macAddr, const char *devName, uint8_t devClass[3])
{
    str2ba(macAddr, &m_macAddress);
    if(devName != nullptr)
        m_devName = std::string(devName);

    if(!devClass)
    {
        for(int i=0; i<3;++i)
            devClass[i] = -1;
    }
    else
        memcpy(m_deviceClass, devClass, 3);
}

CBluetoothDevice::~CBluetoothDevice()
{

}

void CBluetoothDevice::SetDeviceName(const char *name)
{
    m_devName = std::string(name);
}

void CBluetoothDevice::SetDeviceClass(uint8_t devClass[3])
{
    memcpy(m_deviceClass, devClass, 3);
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

std::string CBluetoothDevice::GetDeviceName()
{
    return m_devName;
}
