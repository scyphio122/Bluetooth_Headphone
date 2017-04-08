#include "bluetoothscanner.h"
#include "logger.h"
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>


CBluetoothScanner::CBluetoothScanner(QObject *parent) : QObject(parent),
  m_localAdapterDevId(-1),
  m_localAdapterSocket(-1),
  m_inquiryInfo(nullptr)
{
    m_timeoutTimer.setInterval(M_CONNECTION_TIMEOUT_MS);
    m_timeoutTimer.setSingleShot(true);
    connect(&m_timeoutTimer, SIGNAL(timeout()), this, SLOT(onScanTimeout()));
}

CBluetoothScanner* CBluetoothScanner::GetInstance()
{
    static CBluetoothScanner s_instance;
    return &s_instance;
}

void CBluetoothScanner::m_openLocalAdapter()
{
    LOG_DBG(" ");
    const char* localAdapterMAC = "01:23:45:67:89:AB";;

    m_localAdapterDevId = hci_devid(localAdapterMAC);

    m_localAdapterSocket = hci_open_dev(m_localAdapterDevId);

    LOG_DBG("m_localAdapterDevId: %d, m_localAdapterSocket: %d", m_localAdapterDevId, m_localAdapterSocket);
    if(m_localAdapterDevId < 0 || m_localAdapterSocket < 0)
    {
        LOG_CRITICAL("FAILED TO CREATE SOCKET CONNECTING WITH LOCAL BLUETOOTH ADAPTER!");
        exit(1);
    }
}

void CBluetoothScanner::m_startScanning()
{

}

void CBluetoothScanner::onScanTimeout()
{
    hci_inquiry(m_localAdapterDevId, 8, m_maxScannedDevicesNumber, NULL, &m_inquiryInfo, IREQ_CACHE_FLUSH);
}
