#ifndef BLUETOOTHSCANNER_H
#define BLUETOOTHSCANNER_H

#include <QObject>
#include <QList>
#include <QThread>
#include <QMutex>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include "bluetoothdevice.h"

class CBluetoothScanner : public QObject
{
    Q_OBJECT
public:
    static CBluetoothScanner* GetInstance();

    bool StartScanning();

    void StopScanning();

    void ClearDevList();

signals:
    void nearbyDevicesFound();

public slots:
    void onScanFinished();

private:
    explicit CBluetoothScanner(QObject *parent = 0);

    void m_openLocalAdapter();

    QThread m_thread;

    QMutex m_mutex;

    QList<CBluetoothDevice> m_devicesList;

    /// The value in seconds will be calculated as scan_timeout_s = M_SCAN_TIMEOUT_TICS * 1.28
    const int M_SCAN_TIMEOUT_TICKS = 16;

    const int M_SCAN_DEV_NAME_TIMEOUT_MS = 1000;

    const int M_SCAN_DEV_NAME_BUFFER_SIZE = 15;

    int m_localAdapterDevId;

    int m_localAdapterSocket;

    inquiry_info* m_inquiryInfo;

    const int m_maxScannedDevicesNumber = 255;

    char m_devicesFoundCnt;

private slots:
    void m_onNearbyDevicesFound();
};

#endif // BLUETOOTHSCANNER_H
