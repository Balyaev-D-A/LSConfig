#include "connectform.h"
#include "ui_connectform.h"
#include "stationmanager.h"
#include "serialmanager.h"

ConnectForm::ConnectForm(QWidget *parent) :
    QWidget(parent, Qt::Window),
    ui(new Ui::ConnectForm)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
    StationManager::StationList stList = StationManager::instance()->allStations();
    for (int i=0; i<stList.count(); i++)
        ui->stationBox->addItem(stList[i].name + "  " + stList[i].kks);

    QStringList ports = SerialManager::instance()->allPorts();
    for (int i=0; i<ports.size(); i++)
        ui->portBox->addItem(ports[i]);
    updatePortInfo();
}

ConnectForm::~ConnectForm()
{
    delete ui;
}

void ConnectForm::updatePortInfo()
{
    ui->descriptionLabel->setText(SerialManager::instance()->portDescription(ui->portBox->currentText()));
    ui->manufacturerLabel->setText(SerialManager::instance()->portManufacturer(ui->portBox->currentText()));
    ui->stateLabel->setText((SerialManager::instance()->portBusy(ui->portBox->currentText()) ? "Порт занят." : "Порт свободен."));
}


void ConnectForm::on_connectButton_clicked()
{
    StationManager::instance()->setCurrentStation(ui->portBox->currentIndex());
    SerialManager::instance()->setCurrentPort(ui->portBox->currentText());
    emit choosed();
    close();
}




void ConnectForm::on_cancelButton_clicked()
{
    close();
}

void ConnectForm::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
    emit closed();
}
void ConnectForm::on_portBox_currentIndexChanged(const QString &text)
{
    updatePortInfo();
}

