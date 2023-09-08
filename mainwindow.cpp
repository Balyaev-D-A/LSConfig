#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->connectAction, &QAction::triggered, this, &MainWindow::connectActionTriggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectActionTriggered()
{
    StationSelectForm *stSelForm = new StationSelectForm(this);
    stSelForm->setWindowModality(Qt::WindowModal);
    connect(stSelForm, &StationSelectForm::closed, this, &MainWindow::stationSelFormClosed);
    connect(stSelForm, &StationSelectForm::choosed, this, &MainWindow::stationChoosed);
    stSelForm->show();
}

void MainWindow::stationSelFormClosed()
{
    sender()->deleteLater();
}

void MainWindow::stationChoosed(int index)
{
    if (index < 0) return;
    currStation = StationManager::instance()->getStations()[index];
    while (ui->channelsTable->rowCount()) ui->channelsTable->removeRow(0);
    for (int i=0; i<16; i++)
    {
        ui->channelsTable->insertRow(i);
        if (!currStation.channels[i].active) ui->channelsTable->hideRow(i);
        ui->channelsTable->setItem(i, 0, new QTableWidgetItem(currStation.channels[i].kks));
        ui->channelsTable->setItem(i, 1, new QTableWidgetItem(currStation.channels[i].detType));
    }
}
