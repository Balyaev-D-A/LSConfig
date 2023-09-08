#include "stationselectform.h"
#include "ui_stationselectform.h"
#include "stationmanager.h"

StationSelectForm::StationSelectForm(QWidget *parent) :
    QWidget(parent, Qt::Window),
    ui(new Ui::StationSelectForm)
{
    ui->setupUi(this);
    StationManager::StationList stList = StationManager::instance()->getStations();
    for (int i=0; i<stList.size(); i++) ui->stationBox->addItem(stList[i].name + " KKS: " + stList[i].kks);
}

StationSelectForm::~StationSelectForm()
{
    delete ui;
}

void StationSelectForm::on_chooseButton_clicked()
{
    if (!ui->stationBox->count()) emit choosed(-1);
    else emit choosed(ui->stationBox->currentIndex());
    close();
}

void StationSelectForm::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
    emit closed();
}
