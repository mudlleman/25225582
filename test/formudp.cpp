#include "formudp.h"
#include "ui_formudp.h"

FormUdp::FormUdp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormUdp)
{
    ui->setupUi(this);

    receiver = new QUdpSocket(this);
    receiver->bind(QHostAddress::LocalHost, 6665);
    connect(receiver, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));

    QByteArray datag="hello world!";
    SendData(datag);
}

FormUdp::~FormUdp()
{
    delete ui;
}
void FormUdp::SendData(QByteArray qb)
{

    QUdpSocket *msender = new QUdpSocket(this);


    msender->writeDatagram(qb.data(),qb.size(),QHostAddress::Broadcast,6669);
    delete msender;

}
void FormUdp::readPendingDatagrams()
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
