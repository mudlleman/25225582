#ifndef SPEEDPULSE_H
#define SPEEDPULSE_H

#include <QThread>
#include     <stdio.h>
#include     <stdlib.h>
#include     <unistd.h>
#include     <sys/types.h>
#include     <sys/stat.h>
#include     <fcntl.h>
#include     <termios.h>
#include     <errno.h>
class SpeedPulse : public QThread
{
    Q_OBJECT
public:
    explicit SpeedPulse(QObject *parent = 0);
    void initvalue(long lvalue);
    long  getpulsevalue();
    void run();
private:
    long m_pulse;
signals:
    
public slots:
    
};

#endif // SPEEDPULSE_H
