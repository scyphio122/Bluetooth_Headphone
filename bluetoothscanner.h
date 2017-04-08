#ifndef BLUETOOTHSCANNER_H
#define BLUETOOTHSCANNER_H

#include <QObject>
#include <QList>
#include <QTimer>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

class CBluetoothScanner : public QObject
{
    Q_OBJECT
public:
    static CBluetoothScanner* GetInstance();

    void StartScanning();

    void StopScanning();

    void ClearDevList();
signals:

public slots:
    void onScanTimeout();

private:
    explicit CBluetoothScanner(QObject *parent = 0);

    void m_openLocalAdapter();

    QTimer m_timeoutTimer;

    const int M_CONNECTION_TIMEOUT_MS = 10000;

    int m_localAdapterDevId;

    int m_localAdapterSocket;

    inquiry_info* m_inquiryInfo;

    const int m_maxScannedDevicesNumber = 10;
};

#endif // BLUETOOTHSCANNER_H
