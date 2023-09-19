#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H
#include <QString>
#include <QSerialPortInfo>

class SerialManager
{
public:
    typedef QList<QSerialPortInfo> PortList;
    static SerialManager* instance();
    bool setCurrentPort(QString port);
    QString currentPort();
    PortList allPorts();
private:
    static SerialManager* m_inst;
    QSerialPortInfo *m_currPort = new QSerialPortInfo();
    SerialManager();
    ~SerialManager();
};

#endif // SERIALMANAGER_H
