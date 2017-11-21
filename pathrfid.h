#ifndef PATHRFID_H
#define PATHRFID_H

#include <QObject>
#include "xsserial.h"
#include "owntimer.h"

class PathRfid : public QObject
{
    Q_OBJECT
public:
    explicit PathRfid(QObject *parent = 0);
    
    OWNTimer m_threadTime;
    xsserial *m_serial;
public:
signals:
    void readidsingal(int id);
public slots:
    void GetReadValue();
    
};

#endif // PATHRFID_H
