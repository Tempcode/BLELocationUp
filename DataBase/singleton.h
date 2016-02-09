#ifndef SingleTon_H
#define SingleTon_H

#include <QString>
#include <QObject>

class QSqlTableModel;

namespace DataBase
{
    enum Model { PersonnelInfo, Duty, Title, Anchor, currentPos };
}


class SingleTon : QObject
{
    Q_OBJECT

public:
    static SingleTon *instance();

public slots:
    //Anchor
    bool addAnchor(QString DevAddress, quint32 X, quint64 Y);
    bool delAnchor(QString DevAddress);
    bool changeAnchor(QString DevAddress, quint32 X, quint64 Y);

    //PersonnelInfo
    bool addPersonnelInfo(QString CardAddress, QString name, int sex, QString birthday=" ", QString tel=" ", QString homePhone=" ");
    bool delPersonnelInfo(QString CardAddress);
    bool changePersonnelInfo(QString CardAddress, QString name,int sex, QString birthday=" ", QString tel=" ", QString homePhone=" ");

    //PosRecord
    bool addPosRecord(QString recordtime, QString CardAddress, quint32 x, quint32 y);
    bool delPosRecord(quint32 id);

    /***** Standby interface *****/
    bool add(QString &table, QString &values);
    bool del(QString &table, QString &filter);
    bool execSql(QString &sql);

    /***** initialization *****/
    static bool creatTables();

    /********** Models **********/
    static QSqlTableModel *getModel(DataBase::Model modelName);

private slots:
    void updateModels();

private:
    SingleTon(QObject *parent = 0);
    void initModels();

private:
    static SingleTon    *  theInstance;
    QString                 m_sql;
};

#endif // SingleTon_H
