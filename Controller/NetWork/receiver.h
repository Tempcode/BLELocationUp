#ifndef RECEIVER_H
#define RECEIVER_H

#include "./Controller/Base/baseType.h"
#include <QUdpSocket>
#include <QObject>
#include <QMultiHash>


class Receiver : public QObject
{
    Q_OBJECT

public:
    Receiver(QObject *parent = 0);

public slots:
    void initSocket();

signals:
    void rcv(BLEMonitor bleMonitor);

private slots:
    void readPendingDatagrams();

private:
    void processTheDatagram(char *data/*, QHostAddress sender, quint16 senderPort*/);

private:
    QUdpSocket          *   udpSocket;
    BLEMonitor              bleMonitor;
};

#endif // RECEIVER_H
