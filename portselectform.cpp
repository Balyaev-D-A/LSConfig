#include "portselectform.h"
#include "ui_portselectform.h"

PortSelectForm::PortSelectForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PortSelectForm)
{
    ui->setupUi(this);
}

PortSelectForm::~PortSelectForm()
{
    delete ui;
}
