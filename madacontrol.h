#ifndef MADACONTROL_H
#define MADACONTROL_H

#include <QObject>
#include "xsserial.h"
#include "owntimer.h"
#include "ccontrolbyte.h"
#include <QVector>
class MadaControl : public QThread
{
    Q_OBJECT
public:
    explicit MadaControl(QString comname,QObject *parent = 0);
    void wirtedata(QByteArray qb);
    void controlstep(int steplen);

    void setcurpostion(int bjpostion);
    int getpostion();
    void run();
private :
  //  OWNTimer m_threadTime;
    xsserial *m_serial;
    CcontrolByte ctbyte;
    QString m_comname;
    QVector<int> m_listpostion;

    int m_postion;
    int m_bjpostion;
    int m_willrunstep;

    int temppostion;
    int setpostion;
    int m_turnspeed;

   // QByteArray qba;

    void MadaRunType(int type);
    QVector<uchar> m_tempcharv;

    bool isusenow;
    bool nowtrun;
signals:
    
public slots:
    void GetReadValue();
};

#endif // MADACONTROL_H
