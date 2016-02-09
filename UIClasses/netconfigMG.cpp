#include "netconfigMG.h"
#include "ui_netconfigMG.h"

NetConfigMG::NetConfigMG(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetConfigMG)
{
    ui->setupUi(this);
    setLayout(ui->mainLayout);
}

NetConfigMG::~NetConfigMG()
{
    delete ui;
}
