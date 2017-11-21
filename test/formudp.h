#ifndef FORMUDP_H
#define FORMUDP_H

#include <QWidget>
#include <QtNetwork>
namespace Ui {
class FormUdp;
}

class FormUdp : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormUdp(QWidget *parent = 0);
    ~FormUdp();
        void SendData(QByteArray qb);
private:
    QUdpSocket *sender;
    QUdpSocket *receiver;

    Ui::FormUdp *ui;
public slots:
    void readPendingDatagrams();

};

#endif // FORMUDP_H
