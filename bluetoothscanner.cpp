#include "bluetoothscanner.h"
#include "logger.h"

CBluetoothScanner::CBluetoothScanner(QObject *parent) : QObject(parent)
{

}

CBluetoothScanner* CBluetoothScanner::GetInstance()
{
    static CBluetoothScanner s_instance;
    LOG("m_instance: %p", &s_instance);
    return &s_instance;
}
