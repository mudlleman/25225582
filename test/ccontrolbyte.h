#ifndef CCONTROLBYTE_H
#define CCONTROLBYTE_H

#include <QObject>

class CcontrolByte : public QObject
{
    Q_OBJECT
public:
    explicit CcontrolByte(QObject *parent = 0);
    
    QByteArray GetSpeedByte(int madindex,int speed);
signals:
    
public slots:
    
};

#endif // CCONTROLBYTE_H
