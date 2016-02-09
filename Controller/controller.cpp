#include "controller.h"
#include "./NetWork/receiver.h"
#include "./DataBase/singleton.h"
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDateTime>
#include <QTimer>
#include <QMap>
#include <list>

int cmpFunc(BLEMonitor b1,  BLEMonitor b2)
{//Ascending
    return b1.cRssi < b2.cRssi;
}

Controller::Controller(QObject *parent)
    :QObject(parent)
{
    m_multiHash = new QMultiHash<QString, BLEMonitor>();
    multiHash4process = new QMultiHash<QString, BLEMonitor>();

    QTimer *timer1 = new QTimer(this);
    Receiver *receiver = new Receiver;
//    timer2Duty();

    receiver->moveToThread(&netWorkThread);

    connect(&netWorkThread, &QThread::finished, receiver, &QObject::deleteLater);
    connect(this, &Controller::netStart, receiver, &Receiver::initSocket);
    connect(receiver, &Receiver::rcv, this, &Controller::append2Hash);
    connect(timer1, SIGNAL(timeout()), this, SLOT(timer1Duty()));

    netWorkThread.start();
    emit netStart();
    timer1->start(500);
}

void Controller::timer1Duty()
{
    quint64 start= QDateTime::currentMSecsSinceEpoch();
    QMultiHash<QString, BLEMonitor> tempHash;
    m_multiHash->swap(tempHash);
    *multiHash4process += tempHash;

    /**********************************
     * step1. MultiHash to List
     * step2. For sort list with RSSI
     * step3. According to the sorted stdlist generated Map<mAddr,BLEMonitor>
     * step4. Map items count is equal or greater than 3， remove multiHash4process->key(cAddr)
     * ********************************/ ;
    for(int i = 0; i < m_personCount; i++)
    {
        QList<BLEMonitor> list = multiHash4process->values(m_cAddrKey[i]);// MultiHash keys for Personnel cardAddr BLEMonitor List
        std::list<BLEMonitor> stdList = list.toStdList();               // In order to use std::list.sort
        stdList.sort(cmpFunc);
        QMap<QString, BLEMonitor> mapFilterDuplicate;      // In order to filter duplicate intermediate variable
        QVector<BLEMonitor> top3Rssi; // result of top3 RSSI value mAddr
        BLEMonitor var;
        foreach (var, stdList)
        {
            mapFilterDuplicate.insert(var.mAddr, var);
        }

        //Get top3Rssi mAddr and clean up the multiHash4process meet the conditions item
        if( mapFilterDuplicate.count() >= POINTCOUNT4LOCATING )
        {
            int count = 0;
            foreach (var, mapFilterDuplicate)
            {
                top3Rssi.append(var);
                if(++count == POINTCOUNT4LOCATING)
                    break;
            }
            emit top3Monitor(top3Rssi);
            multiHash4process->remove(var.cAddr);
        }
    }
    qDebug() << QDateTime::currentMSecsSinceEpoch() - start;
}



void Controller::append2Hash(BLEMonitor bleMonitor)
{
    m_multiHash->insertMulti(bleMonitor.cAddr, bleMonitor);
}

Controller::~Controller()
{
    netWorkThread.quit();
    netWorkThread.wait();
}
