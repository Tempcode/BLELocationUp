#include "receiver.h"

Receiver::Receiver(QObject *parent)
    :QObject(parent)
{

}

void Receiver::initSocket()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, 5687);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

void Receiver::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
        char data[BLEMonitorLENGTH];
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(data, BLEMonitorLENGTH,
                                &sender, &senderPort);

        processTheDatagram(data);
    }
}

void Receiver::processTheDatagram(char *data/*, QHostAddress sender, quint16 senderPort*/)
{
    bleMonitor.mAddr.clear();
    bleMonitor.cAddr.clear();
    bleMonitor.cRssi = data[12];// RSSI;

    qint8   intByte = 0;
    for(int i = 0; i < 6; i++) //mAddr
    {
        intByte = data[i];
        bleMonitor.mAddr.append(QString::number(intByte, 16));
    }

    for(int i = 6; i < 12; i++) //cAddr
    {
        intByte = data[i];
        bleMonitor.cAddr.append(QString::number(intByte, 16));
    }

    emit rcv(bleMonitor);
}
