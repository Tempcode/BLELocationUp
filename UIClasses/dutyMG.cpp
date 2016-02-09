#include "dutyMG.h"
#include "ui_dutymg.h"
#include "./DataBase/singleton.h"
#include <QTableView>
#include <QStringList>
#include <QSqlTableModel>
#include <QAbstractItemModel>

DutyMG::DutyMG(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DutyMG)
{
    ui->setupUi(this);
    m_dutyTableView = ui->DutyTableView;
    initTableWidget();
    ui->mainLayout->addWidget(m_dutyTableView);
    setLayout(ui->mainLayout);
}

void DutyMG::initTableWidget()
{
    model = SingleTon::getModel(DataBase::Duty);
    m_dutyTableView->setModel(model);
}

void DutyMG::resizeEvent(QResizeEvent * event)
{
    int width = event->size().width()-20;
    int colCount = model->columnCount();
    for(int i = 0; i < model->rowCount(); i++)
    {
        m_dutyTableView->setColumnWidth(0,width/colCount);
        m_dutyTableView->setColumnWidth(1,width/colCount);
        m_dutyTableView->setColumnWidth(2,width/colCount);
    }
}

DutyMG::~DutyMG()
{
    delete ui;
}
