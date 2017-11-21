#ifndef GETPATHID_H
#define GETPATHID_H

#include <QObject>
#include "owntimer.h".h"
#include "xsserial.h"
#include <QVector>

class GetPathID : public QObject
{
    Q_OBJECT
public:
    explicit GetPathID(QObject *parent = 0);
private:
    OWNTimer m_threadTime;
    xsserial *m_serial;
public:
signals:
    void readidsingal(int id);
public slots:
    void GetReadValue();
    
};

#endif // GETPATHID_H
