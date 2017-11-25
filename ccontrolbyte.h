#ifndef CCONTROLBYTE_H
#define CCONTROLBYTE_H

#include <QObject>

class CcontrolByte : public QObject
{
    Q_OBJECT
public:
    explicit CcontrolByte(QObject *parent = 0);
    
    QByteArray GetSpeedByte(int madindex,int speed);
    QByteArray GetPostionByte(int madindex,int speed);
    QByteArray GetStateOPen(int madindex,bool start);
signals:
    
public slots:
    
};

#endif // CCONTROLBYTE_H
