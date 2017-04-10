#include "bluetoothscanner.h"
#include "logger.h"
#include "mutex.h"
#include "bluetoothdevice.h"
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

CBluetoothScanner::CBluetoothScanner(QObject *parent) : QObject(parent),
  m_localAdapterDevId(-1),
  m_localAdapterSocket(-1),
  m_inquiryInfo(nullptr),
  m_devicesFoundCnt(-1)
{
    this->moveToThread(&m_thread);
    connect(this, SIGNAL(destroyed(QObject*)), &m_thread, SLOT(deleteLater()));
    connect(this, SIGNAL(nearbyDevicesFound()), this, SLOT(m_onNearbyDevicesFound()));
    m_thread.start();

    m_openLocalAdapter();
}

CBluetoothScanner* CBluetoothScanner::GetInstance()
{
    static CBluetoothScanner s_instance;
    return &s_instance;
}

void CBluetoothScanner::m_openLocalAdapter()
{
    LOG_DBG(" ");
    CMutex(&(this->m_mutex));

    /// Get the Device ID of the working adapter
    m_localAdapterDevId = hci_get_route(NULL);

    /// Open the device
    m_localAdapterSocket = hci_open_dev(m_localAdapterDevId);

    LOG_DBG("m_localAdapterDevId: %d, m_localAdapterSocket: %d", m_localAdapterDevId, m_localAdapterSocket);
    if(m_localAdapterDevId < 0 || m_localAdapterSocket < 0)
    {
        LOG_CRITICAL("FAILED TO CREATE SOCKET CONNECTING WITH LOCAL BLUETOOTH ADAPTER!");
        LOG_ERRNO();
        exit(1);
    }

}

bool CBluetoothScanner::StartScanning()
{
    LOG_DBG(" ");
    CMutex(&(this->m_mutex));

    if(m_localAdapterSocket == -1)
    {
        LOG_CRITICAL("Bluetooth adapter socket is not opened");
        return false;
    }

    if(m_inquiryInfo != nullptr)
    {
        free(m_inquiryInfo);
        m_inquiryInfo = nullptr;
    }

    /// Create list which will hold the scanned blutooth devices
    m_inquiryInfo = (inquiry_info*)malloc(m_maxScannedDevicesNumber * sizeof(inquiry_info));
    if(m_inquiryInfo == nullptr)
    {
        LOG_CRITICAL("CANNOT ALLOCATE MEMORY FOR INQUIRY DATA");
    }


    LOG_INFO("Scan has started, SCAN_TIMEOUT: %f, MAX DISCOVERED DEVICES NUMBER: %d", M_SCAN_TIMEOUT_TICKS*1.28f, m_maxScannedDevicesNumber);
    m_devicesList.clear();
    /// Start scan
    m_devicesFoundCnt = hci_inquiry(m_localAdapterDevId, M_SCAN_TIMEOUT_TICKS, m_maxScannedDevicesNumber, NULL, &m_inquiryInfo, IREQ_CACHE_FLUSH);

    if(m_devicesFoundCnt == -1)
    {
        LOG_CRITICAL("Error during scanning");
        return false;
    }

    LOG_DBG("Scan finished. Found: %d devices", m_devicesFoundCnt);

    emit nearbyDevicesFound();
    return true;
}

void CBluetoothScanner::m_onNearbyDevicesFound()
{
    LOG_DBG("m_devicesFoundCnt: %d", m_devicesFoundCnt);
    int retval = 0;
    if(m_devicesFoundCnt <= 0)
        return;

    for(int i=0; i<m_devicesFoundCnt; ++i)
    {
        char name[M_SCAN_DEV_NAME_BUFFER_SIZE];
        CBluetoothDevice dev(&(m_inquiryInfo[i].bdaddr));
        dev.SetDeviceClass(m_inquiryInfo[i].dev_class);

        retval = hci_read_remote_name(m_localAdapterSocket, &(m_inquiryInfo[i].bdaddr), sizeof(name),  name, M_SCAN_DEV_NAME_TIMEOUT_MS);
        if(retval == -1)
        {
            LOG_CRITICAL("Could not get the device name of MAC: %s. Ignoring it...", dev.GetMacString().c_str());
            continue;
        }

        dev.SetDeviceName(const_cast<const char*>(name));

        LOG_INFO("Device Found! Name: %s, MAC: %s", dev.GetDeviceName().c_str(), dev.GetMacString().c_str());
        m_devicesList.append(dev);
    }
}

void CBluetoothScanner::onScanFinished()
{

}
