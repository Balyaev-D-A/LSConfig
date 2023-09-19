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
    delete m_currPort;
}

bool SerialManager::setCurrentPort(QString port)
{
    delete m_currPort;
    m_currPort = new QSerialPortInfo(port);
    return !m_currPort->isNull();
}

QString SerialManager::currentPort()
{
    return m_currPort->portName();
}

SerialManager::PortList SerialManager::allPorts()
{
    return QSerialPortInfo::availablePorts();
}
