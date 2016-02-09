#include "configuration.h"
#include "ui_configuration.h"
#include "personnelMG.h"
#include "dutyMG.h"
#include "anchorMG.h"
#include "netconfigMG.h"
#include "titleMG.h"
#include <QSplitter>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QResizeEvent>

Configuration::Configuration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Configuration)
{
    setWindowFlags(Qt::Window);
    ui->setupUi(this);
    m_mainLayout = new QHBoxLayout(this);
    m_groupBoxLayout = new QHBoxLayout();
    m_splitter = new QSplitter(Qt::Horizontal, this);

    m_personnelWidget = new PersonnelMG(this);
    m_dutyWidget = new DutyMG(this);
    m_titleWidget = new TitleMG(this);
    m_anchorWidget = new AnchorMG(this);
    m_netConfigWidget = new NetConfigMG(this);

    m_stackedWidget = new QStackedWidget(this);
    m_stackedWidget->addWidget(m_personnelWidget);
    m_stackedWidget->addWidget(m_dutyWidget);
    m_stackedWidget->addWidget(m_titleWidget);
    m_stackedWidget->addWidget(m_anchorWidget);
    m_stackedWidget->addWidget(m_netConfigWidget);
    m_groupBoxLayout->addWidget(m_stackedWidget);

    ui->groupBox->setLayout(m_groupBoxLayout);

    m_splitter->addWidget(ui->listWidget);
    m_splitter->addWidget(ui->groupBox);
    m_splitter->setStretchFactor(0, 2);
    m_splitter->setStretchFactor(1, 8);

    m_mainLayout->addWidget(m_splitter);
    setLayout(m_mainLayout);
    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), m_stackedWidget, SLOT(setCurrentIndex(int)));
    connect(ui->listWidget, SIGNAL(currentTextChanged(QString)), this, SLOT(setGroupBoxTitle(QString)));
}

void Configuration::setGroupBoxTitle(QString title)
{
    ui->groupBox->setTitle(title);
}

void Configuration::setCurrentIndex(int index)
{
    ui->listWidget->setCurrentRow(index);
}

void Configuration::paintEvent(QPaintEvent * evet)
{
    evet->accept();
    ui->listWidget->resize(ui->listWidget->width(), this->height()-40);
    ui->groupBox->resize(ui->groupBox->width(), this->height()-40);
    int width = ui->groupBox->width()-10;
    int height = ui->groupBox->height()-10;
    emit resizeEvent( new QResizeEvent( QSize(width, height), m_stackedWidget->currentWidget()->size() ) );
}

Configuration::~Configuration()
{
    delete ui;
}
