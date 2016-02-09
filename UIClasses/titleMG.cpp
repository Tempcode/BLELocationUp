#include "titleMG.h"
#include "ui_titleMG.h"
#include "./DataBase/singleton.h"
#include <QTableView>
#include <QStringList>
#include <QSqlTableModel>
#include <QAbstractItemModel>
#include <QDebug>

TitleMG::TitleMG(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleMG)
{
    ui->setupUi(this);
    m_titleTableView = ui->TitleTableView;
    initTableWidget();
    ui->mainLayout->addWidget(m_titleTableView);
    setLayout(ui->mainLayout);
}

void TitleMG::initTableWidget()
{
    model = SingleTon::getModel(DataBase::Title);
    m_titleTableView->setModel(model);
}

void TitleMG::resizeEvent(QResizeEvent * event)
{
    int width = event->size().width()-20;
    int colCount = model->columnCount();
    for(int i = 0; i < model->rowCount(); i++)
    {
        m_titleTableView->setColumnWidth(0,width/colCount);
        m_titleTableView->setColumnWidth(1,width/colCount);
    }
}

TitleMG::~TitleMG()
{
    delete ui;
}
