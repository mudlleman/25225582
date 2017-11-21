#include "udp.h"

Udp::Udp(QObject *parent) :
    QObject(parent)
{
    receiver = new QUdpSocket(this);
    receiver->bind(QHostAddress::LocalHost, 6663);
    connect(receiver, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));

    QUdpSocket *sender;
    sender = new QUdpSocket(this);

    QByteArray datag="hello world!";
    SendData(datag);
}

void Udp::SendData(QByteArray qb)
{
   // sender->writeDatagram(qb.data(),qb.size(),QHostAddress::Broadcast,6665);
}
void Udp::readPendingDatagrams()
{
    while (receiver->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(receiver->pendingDatagramSize());
        receiver->readDatagram(datagram.data(), datagram.size());
        QString s = datagram;
        qDebug()<<s;
        //数据接收在datagram里
        /* readDatagram 函数原型
    qint64 readDatagram(char *data,qint64 maxSize,QHostAddress *address=0,quint16 *port=0)
    */
    }
}
