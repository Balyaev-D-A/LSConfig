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

}

ConnectForm::~ConnectForm()
{
    delete ui;
}
