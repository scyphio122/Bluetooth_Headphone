#ifndef BLUETOOTHSCANNER_H
#define BLUETOOTHSCANNER_H

#include <QObject>
#include <QList>
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


private:
    explicit CBluetoothScanner(QObject *parent = 0);

    void m_openLocalAdapter();

    int m_localAdapterDevId;

    int m_localAdapterSocket;
};

#endif // BLUETOOTHSCANNER_H
