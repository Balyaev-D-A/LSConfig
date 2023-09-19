#include <QSerialPortInfo>
#include "serialmanager.h"

SerialManager *SerialManager::m_inst = nullptr;

SerialManager* SerialManager::instance()
{
    if (m_inst == nullptr) m_inst = new SerialManager();
    return m_inst;
}

SerialManager::SerialManager()
{

}

SerialManager::~SerialManager()
{

}

void SerialManager::setCurrentPort(QString port)
{
    m_currPort = port;
}

QString SerialManager::currentPort()
{
    return m_currPort;
}

QStringList SerialManager::allPorts()
{
    QStringList result;
    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    for (int i=0; i<portList.size(); i++)
        result.append(portList[i].portName());
    return result;
}

bool SerialManager::portBusy(QString portName)
{
    QSerialPortInfo port(portName);
    return port.isBusy();
}

QString SerialManager::portManufacturer(QString portName)
{
    QSerialPortInfo port(portName);
    return port.description();
}
