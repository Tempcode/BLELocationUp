#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "./Controller/Base/baseType.h"
#include <QObject>
#include <QMultiHash>
#include <QThread>
#include <QVector>
#include <QSqlTableModel>

class Controller: public QObject
{
    Q_OBJECT
    QThread netWorkThread;
public:
    Controller(QObject *parent = 0);
    ~Controller();
    void append2Hash(BLEMonitor bleMonitor);

public slots:
    void timer1Duty();
//    void timer2Duty();

signals:
    void netStart();
    void top3Monitor(QVector<BLEMonitor> top3RSSIVect);

private:
    QMultiHash<QString, BLEMonitor>     *   m_multiHash;
    QMultiHash<QString, BLEMonitor>     *   multiHash4process;
    QSqlTableModel                      *   m_personnelInfoModel;
    QList<QString>                          m_cAddrKey;     // Personnel cardAddr
    int                                     m_personCount;  //Personnel Count
};

#endif // CONTROLLER_H
