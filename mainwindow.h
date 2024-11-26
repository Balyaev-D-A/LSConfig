#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamReader>
#include <QQueue>
#include "stationmanager.h"
#include "connectform.h"
#include "device.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    StationManager::Station currStation;
    ConnectForm *stationSelForm;
    Device device;
    bool connected;
    bool firstTime;
    Device::TChannelConfig currChanConf;
    Device::TDeviceInfo currDevInfo;
    void fillUOMBox();
    void connectToDevice();
    void disconnectFromDevice();
    void updateMeasures();
    void updateChanInfo();
    void displayChanConfig(int chanNumber);
    int currentChannel();
    QString UOMCodeToString(quint16 code);

protected:
    void timerEvent(QTimerEvent *e);

private slots:
    void stationSelFormClosed();
    void connectActionTriggered();
    void connectionChoosed();
};
#endif // MAINWINDOW_H
