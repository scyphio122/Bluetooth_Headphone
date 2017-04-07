#ifndef BLUETOOTHSCANNER_H
#define BLUETOOTHSCANNER_H

#include <QObject>
#include <QList>


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

};

#endif // BLUETOOTHSCANNER_H
