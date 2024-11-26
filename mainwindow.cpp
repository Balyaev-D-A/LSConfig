#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialmanager.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->connectAction, &QAction::triggered, this, &MainWindow::connectActionTriggered);
    ui->channelsTable->hideColumn(0);
    fillUOMBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectActionTriggered()
{
    ConnectForm *connectForm = new ConnectForm(this);
    connect(connectForm, &ConnectForm::closed, this, &MainWindow::stationSelFormClosed);
    connect(connectForm, &ConnectForm::choosed, this, &MainWindow::connectionChoosed);
    connectForm->show();
}

void MainWindow::stationSelFormClosed()
{
    sender()->deleteLater();
}

void MainWindow::connectionChoosed()
{
    currStation = StationManager::instance()->currentStation();
    while (ui->channelsTable->rowCount()) ui->channelsTable->removeRow(0);
    for (int i=0; i<16; i++)
    {
        ui->channelsTable->insertRow(i);
        if (!currStation.channels[i].active) ui->channelsTable->hideRow(i);
        ui->channelsTable->setItem(i, 0, new QTableWidgetItem(i));
        ui->channelsTable->setItem(i, 1, new QTableWidgetItem(currStation.channels[i].kks));
        ui->channelsTable->setItem(i, 2, new QTableWidgetItem(currStation.channels[i].detType));
    }
    ui->channelsTable->selectRow(0);
}

void MainWindow::fillUOMBox()
{
    ui->uomBox->addItem("---", 255);
    ui->uomBox->addItem("Гр/ч", 1);
    ui->uomBox->addItem("Бэр/ч", 2);
    ui->uomBox->addItem("Зв/ч", 3);
    ui->uomBox->addItem("Р/ч", 4);
    ui->uomBox->addItem("Н/(м²*с)", 5);
    ui->uomBox->addItem("Бк/м³", 8);
    ui->uomBox->addItem("Ки/л", 9);
    ui->uomBox->addItem("1/(мин*см²)", 10);
    ui->uomBox->addItem("Гр", 16);
    ui->uomBox->addItem("Рад", 17);
    ui->uomBox->addItem("Зв", 18);
    ui->uomBox->addItem("мг/м³", 32);
    ui->uomBox->addItem("%", 48);
    ui->uomBox->addItem("имп/с", 49);
    ui->uomBox->addItem("°С", 50);
    ui->uomBox->addItem("Вт", 51);
    ui->uomBox->addItem("В", 52);
    ui->uomBox->addItem("сек", 53);
    ui->uomBox->addItem("м³", 54);
    ui->uomBox->addItem("м³/ч", 55);
    ui->uomBox->addItem("м³/с", 56);
    ui->uomBox->addItem("л/мин", 57);
}

QString MainWindow::UOMCodeToString(quint16 code)
{
    switch (code) {
    case 1:
        return "Гр/ч";
        break;
    case 2:
        return "Бэр/ч";
        break;
    case 3:
        return "Зв/ч";
        break;
    case 4:
        return "Р/ч";
        break;
    case 5:
        return "Н/(м²*с)";
        break;
    case 8:
        return "Бк/м³";
        break;
    case 9:
        return "Ки/л";
        break;
    case 10:
        return "1/(мин*см²)";
        break;
    case 16:
        return "Гр";
        break;
    case 17:
        return "Рад";
        break;
    case 18:
        return "Зв";
        break;
    case 32:
        return "мг/м³";
        break;
    case 48:
        return "%";
        break;
    case 49:
        return "имп/с";
        break;
    case 50:
        return "°С";
        break;
    case 51:
        return "Вт";
        break;
    case 52:
        return "В";
        break;
    case 53:
        return "сек";
        break;
    case 54:
        return "м³";
        break;
    case 55:
        return "м³/ч";
        break;
    case 56:
        return "м³/с";
        break;
    case 57:
        return "л/мин";
        break;
    default:
        return "---";
    }
}

void MainWindow::connectToDevice()
{
    if (!device.connectToDevice(SerialManager::instance()->currentPort(), StationManager::instance()->currentStation().address)) {
        QMessageBox::critical(this, "Ошибка подключения!!!", device.errorString());
        return;
    }
    connected = true;
    firstTime = true;
    startTimer(1);
}

void MainWindow::updateMeasures()
{
    device.getCurrentInfo(&currDevInfo);
    for (int i=0; i<ui->channelsTable->rowCount(); i++)
    {
        if (ui->channelsTable->isRowHidden(i)) continue;
        ui->channelsTable->setItem(i, 2, new QTableWidgetItem(QString("%1").arg(currDevInfo.m_cInfo[i].m_fsValue, 0, 'E')));
    }
    updateChanInfo();
    if (firstTime)
}

void MainWindow::updateChanInfo()
{

}

void MainWindow::timerEvent(QTimerEvent *e)
{
    updateMeasures();
}
