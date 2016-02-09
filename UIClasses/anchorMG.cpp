#include "anchorMG.h"
#include "ui_anchorMG.h"
#include "./DataBase/singleton.h"
#include <QTableView>
#include <QStringList>
#include <QSqlTableModel>
#include <QAbstractItemModel>

AnchorMG::AnchorMG(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnchorMG)
{
    ui->setupUi(this);
    m_anchorTableView = ui->AnchorTableView;
    initTableWidget();
    ui->mainLayout->addWidget(m_anchorTableView);
    setLayout(ui->mainLayout);
}

void AnchorMG::initTableWidget()
{
    model = SingleTon::getModel(DataBase::Anchor);
    m_anchorTableView->setModel(model);
}

void AnchorMG::resizeEvent(QResizeEvent * event)
{
    int width = event->size().width()-20;
    int colCount = model->columnCount();
    for(int i = 0; i < model->rowCount(); i++)
    {
        m_anchorTableView->setColumnWidth(0,width/colCount);
        m_anchorTableView->setColumnWidth(1,width/colCount);
        m_anchorTableView->setColumnWidth(2,width/colCount);
    }
}

AnchorMG::~AnchorMG()
{
    delete ui;
}
