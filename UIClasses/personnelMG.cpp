#include "personnelMG.h"
#include "ui_personnelMG.h"
#include "./DataBase/singleton.h"
#include <QTableView>
#include <QStringList>
#include <QSqlTableModel>
#include <QAbstractItemModel>
#include <QDebug>

PersonnelMG::PersonnelMG(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonnelMG)
{
    ui->setupUi(this);
    m_personnelTableView = ui->PersonnelTableView;
    initTableView();
    ui->mainLayout->addWidget(m_personnelTableView);
    setLayout(ui->mainLayout);
}

void PersonnelMG::initTableView()
{
    model = SingleTon::getModel(DataBase::PersonnelInfo);
    m_personnelTableView->setModel(model);
}

void PersonnelMG::resizeEvent(QResizeEvent * event)
{
    int width = event->size().width()-20;
    int colCount = model->columnCount();
    for(int i = 0; i < model->rowCount(); i++)
    {
        m_personnelTableView->setColumnWidth(0,width/colCount);
        m_personnelTableView->setColumnWidth(1,width/colCount);
        m_personnelTableView->setColumnWidth(2,width/colCount);
        m_personnelTableView->setColumnWidth(3,width/colCount);
        m_personnelTableView->setColumnWidth(4,width/colCount);
        m_personnelTableView->setColumnWidth(5,width/colCount);
        m_personnelTableView->setColumnWidth(6,width/colCount);
        m_personnelTableView->setColumnWidth(7,width/colCount);
    }
}

PersonnelMG::~PersonnelMG()
{
    delete ui;
}
