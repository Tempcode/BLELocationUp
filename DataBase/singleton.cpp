#include "singleton.h"
#include "Controller/Base/baseType.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QString>
#include <QDir>
#include <QSqlError>
#include <QSqlTableModel>
#include <QTimer>


SingleTon * SingleTon::theInstance = NULL;
static QSqlQuery    *gs_query = NULL;
static QSqlTableModel   *gs_currentPosModel = NULL;
static QSqlTableModel   *gs_personnelInfoModel = NULL;
static QSqlTableModel   *gs_dutyModel = NULL;
static QSqlTableModel   *gs_anchorModel = NULL;
static QSqlTableModel   *gs_titleModel = NULL;
static QSqlDatabase gs_db = QSqlDatabase::addDatabase("QSQLITE", "SingleTon");

SingleTon  * SingleTon::instance()
{
    if( NULL == theInstance )
        theInstance = new SingleTon();
    return theInstance;
}

//====================Anchor=======================
bool SingleTon::addAnchor(QString DevAddress, quint32 X, quint64 Y)
{
    if(DevAddress.length() == 12)
    {
        m_sql.clear();
        m_sql = QString::fromUtf8("insert into Anchor values (%1, %2, %3);").arg(DevAddress).arg(X).arg(Y);
        return gs_query->exec(m_sql);
    }
    return false;
}

bool SingleTon::delAnchor(QString DevAddress)
{
    if(DevAddress.length() == 12)
    {
        m_sql.clear();
        m_sql = QString::fromUtf8("delete from Anchor where DevAddress = %1;").arg(DevAddress);
        return gs_query->exec(m_sql);
    }
    return false;
}

bool SingleTon::changeAnchor(QString DevAddress, quint32 X, quint64 Y)
{
    if(DevAddress.length() == 12)
    {
        m_sql.clear();
        m_sql = QString::fromUtf8("update Anchor set X=%1, Y=%2 where DevAddress = %3;").arg(X).arg(Y).arg(DevAddress);
        return gs_query->exec(m_sql);
    }
    return false;
}

//=====================PersonnelInfo======================
bool SingleTon::addPersonnelInfo(QString CardAddress, QString name, int sex,
                      QString birthday, QString tel, QString homePhone)
{
    if(CardAddress.length() == 12)
    {
        m_sql.clear();
        m_sql = QString::fromUtf8("insert into PersonnelInfo values (%1,%2,%3,%4,%5,%6);")
                .arg(CardAddress).arg(name).arg(sex).arg(birthday).arg(tel).arg(homePhone);
        return gs_query->exec(m_sql);
    }
    return false;
}

bool SingleTon::delPersonnelInfo(QString CardAddress)
{
    if(CardAddress.length() == 12)
    {
        m_sql.clear();
        m_sql = QString::fromUtf8("delete from PersonnelInfo where DevAddress = %1;").arg(CardAddress);
        return gs_query->exec(m_sql);
    }
    return false;
}
bool SingleTon::changePersonnelInfo(QString CardAddress, QString name, int sex,
                         QString birthday, QString tel, QString homePhone)
{
    if(CardAddress.length() == 12)
    {
        m_sql.clear();
        m_sql = QString::fromUtf8("update PersonnelInfo set "
                                    "DevAddress=%1, Name=%2, Sex=%3, BirthDay=%4, TelePhone=%5, HomePhone=%6 "
                                    "where DevAddress = %7;")
                .arg(CardAddress).arg(name).arg(sex).arg(birthday).arg(tel).arg(homePhone).arg(CardAddress);
        return gs_query->exec(m_sql);
    }
    return false;
}

//=====================PosRecord======================
bool SingleTon::addPosRecord(QString recordtime, QString CardAddress, quint32 x, quint32 y)
{
    if(CardAddress.length() == 12)
    {
        m_sql.clear();
        m_sql = QString::fromUtf8("insert into PosRecord values (%1,%2,%3,%4);")
                .arg(recordtime).arg(CardAddress).arg(x).arg(y);
        return gs_query->exec(m_sql);
    }
    return false;
}

bool SingleTon::delPosRecord(quint32 id)
{
    m_sql.clear();
    m_sql = QString::fromUtf8("delete from PosRecord where Id=%1;")
            .arg(id);
    return gs_query->exec(m_sql);
}
//====================Models=====================
QSqlTableModel  *SingleTon::getModel(DataBase::Model modelName)
{
    QSqlTableModel * temp = NULL;
    switch (modelName) {
    case DataBase::PersonnelInfo:
        temp = gs_personnelInfoModel;
        break;
    case DataBase::Duty:
        temp = gs_dutyModel;
        break;
    case DataBase::Title:
        temp = gs_titleModel;
        break;
    case DataBase::Anchor:
        temp = gs_anchorModel;
        break;
    case DataBase::currentPos:
        temp = gs_currentPosModel;
        break;
    }
    return temp;
}

//=====================Standby interface==================
bool SingleTon::execSql(QString &sql)
{
    return gs_query->exec(sql);
}

bool SingleTon::add(QString &table, QString &values)
{
    m_sql.clear();
    m_sql = QString::fromUtf8("insert into %1 values (%2);").arg(table).arg(values);
    return gs_query->exec(m_sql);
}

bool SingleTon::del(QString &table, QString &filter)
{
    m_sql.clear();
    m_sql = QString::fromUtf8("delete from %1 where %2;").arg(table).arg(filter);
    return gs_query->exec(m_sql);
}

//=====================initialization======================
bool SingleTon::creatTables()
{
    QDir filePath;
    if(! filePath.exists(DBFilePath))
        filePath.mkpath(DBFilePath);

    QSqlQuery *gs_query = NULL;
    QSqlDatabase gs_db = QSqlDatabase::addDatabase("QSQLITE", "SingleTonCreateTables");
    gs_db.setDatabaseName(DBFileName);
    if(gs_db.open())
        gs_query = new QSqlQuery(gs_db);

    gs_db.transaction();
    QString tempSql;
    tempSql = QString::fromUtf8(CREATE_ANCHOR);
    bool createAnchor = gs_query->exec(tempSql);

    tempSql.clear();
    tempSql = QString::fromUtf8(CREATE_PERSONNELINFO);
    bool createPersonnelInfo = gs_query->exec(tempSql);

    tempSql.clear();
    tempSql = QString::fromUtf8(CREATE_POSRECORD);
    bool createPosRecord = gs_query->exec(tempSql);

    tempSql.clear();
    tempSql = QString::fromUtf8(CREATE_VIEW_CURRENTPOS);
    bool createViewCurrentPos = gs_query->exec(tempSql);

    tempSql.clear();;
    tempSql = QString::fromUtf8(CREATE_DUTY);
    bool createDuty = gs_query->exec(tempSql);

    tempSql.clear();
    tempSql = QString::fromUtf8(CREATE_TITLE);
    bool createTitle = gs_query->exec(tempSql);
    gs_db.commit();

    return ( createAnchor && createPersonnelInfo && createPosRecord
             && createViewCurrentPos && createDuty && createTitle);
}


SingleTon::SingleTon(QObject *parent)
    :QObject(parent)
{
    QDir filePath;
    if(! filePath.exists(DBFilePath))
        filePath.mkpath(DBFilePath);

    gs_db.setDatabaseName(DBFileName);
    if(gs_db.open())
    {
        gs_query = new QSqlQuery(gs_db);
        gs_query->exec(FOREIGN_KEY_ON);
        initModels();
    }
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateModels()));
    timer->start(5000);
}

void SingleTon::updateModels()
{
    gs_personnelInfoModel->select();
    gs_dutyModel->select();
    gs_titleModel->select();
    gs_anchorModel->select();
    gs_currentPosModel->select();
}

void SingleTon::initModels()
{
    gs_personnelInfoModel = new QSqlTableModel(0, gs_db);
    gs_dutyModel = new QSqlTableModel(0, gs_db);
    gs_titleModel = new QSqlTableModel(0, gs_db);
    gs_anchorModel = new QSqlTableModel(0, gs_db);
    gs_currentPosModel = new QSqlTableModel(0, gs_db);

    gs_personnelInfoModel->setTable(PersonnelInfoTableName);
    gs_dutyModel->setTable(DutyTableName);
    gs_titleModel->setTable(TitleTableName);
    gs_anchorModel->setTable(AnchorTableName);
    gs_currentPosModel->setTable(CurrentPosViewName);


    gs_anchorModel->setHeaderData(0,Qt::Horizontal, "设备编号");
    gs_anchorModel->setHeaderData(1,Qt::Horizontal, "深度(m)");
    gs_anchorModel->setHeaderData(2,Qt::Horizontal, "距洞左侧距离(m)");

    gs_titleModel->setHeaderData(0,Qt::Horizontal, "编号");
    gs_titleModel->setHeaderData(1,Qt::Horizontal, "职务");

    gs_dutyModel->setHeaderData(0,Qt::Horizontal, "班次序号");
    gs_dutyModel->setHeaderData(1,Qt::Horizontal, "开始时间");
    gs_dutyModel->setHeaderData(2,Qt::Horizontal, "结束时间");

    gs_personnelInfoModel->setHeaderData(0,Qt::Horizontal, "卡编号");
    gs_personnelInfoModel->setHeaderData(1,Qt::Horizontal, "姓名");
    gs_personnelInfoModel->setHeaderData(2,Qt::Horizontal, "性别");
    gs_personnelInfoModel->setHeaderData(3,Qt::Horizontal, "出生年月");
    gs_personnelInfoModel->setHeaderData(4,Qt::Horizontal, "职务");
    gs_personnelInfoModel->setHeaderData(5,Qt::Horizontal, "班次");
    gs_personnelInfoModel->setHeaderData(6,Qt::Horizontal, "电话");
    gs_personnelInfoModel->setHeaderData(7,Qt::Horizontal, "家庭电话");
}
