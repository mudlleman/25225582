#ifndef NAVMANGER_H
#define NAVMANGER_H

#include <QObject>
#include "owntimer.h"
#include "xsserial.h"
#include <QVector>
#include "ludp.h"
#include "getnavigation.h"

struct NvCal
{
    int nvcalnuber;
    int nvvalue;
    QTime caltime;
    //int number;
};

class NavManger : public QObject
{
    Q_OBJECT
public:
    explicit NavManger(int nvmuber,QObject *parent = 0);

    void SetCanTurn(bool direct);
     float GetNavigationValue(int devno);
private:
    void GetSendValue( unsigned char * sendvalue,int no);

private:
    OWNTimer m_threadTime;
    xsserial *m_serial;
    NvCal*nvcal;
    GetNavigation *getnav;
    int m_nvnuber;

    
signals:
    
public slots:
     void GetReadValue();
    
};

#endif // NAVMANGER_H
