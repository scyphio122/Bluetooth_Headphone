#include "bluetoothscanner.h"
#include "logger.h"
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>


CBluetoothScanner::CBluetoothScanner(QObject *parent) : QObject(parent),
  m_localAdapterDevId(-1)
{

}

CBluetoothScanner* CBluetoothScanner::GetInstance()
{
    static CBluetoothScanner s_instance;
    return &s_instance;
}

void CBluetoothScanner::m_openLocalAdapter()
{
    const char* localAdapterMAC = "01:23:45:67:89:AB";;

    m_localAdapterDevId = hci_devid(localAdapterMAC);

    m_localAdapterSocket = hci_open_dev(m_localAdapterDevId);

    if(m_localAdapterDevId < 0 || m_localAdapterSocket < 0)
    {

    }
}
