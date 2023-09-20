#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H
#include <QString>

class SerialManager
{
public:
    static SerialManager* instance();
    void setCurrentPort(QString port);
    QString currentPort();
    QStringList allPorts();
    QString portManufacturer(QString portName);
    bool portBusy(QString portName);
    QString portDescription(QString portName);
private:
    static SerialManager* m_inst;
    QString m_currPort;
    SerialManager();
    ~SerialManager();
};

#endif // SERIALMANAGER_H
