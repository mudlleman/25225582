#ifndef UDP_H
#define UDP_H

#include <QObject>
#include <QtNetwork>

class Udp : public QObject
{
    Q_OBJECT
public:
    explicit Udp(QObject *parent = 0);
    void SendData(QByteArray qb);
private:
    QUdpSocket *sender;
    QUdpSocket *receiver;
    
signals:
    
public slots:
    void readPendingDatagrams();
    
};

#endif // UDP_H
