#ifndef GPIOPMW_H
#define GPIOPMW_H

#include <QObject>
#include <QThread>
#include     <stdio.h>
#include     <stdlib.h>
#include     <unistd.h>
#include     <sys/types.h>
#include     <sys/stat.h>
#include     <fcntl.h>
#include     <termios.h>
#include     <errno.h>
class GpioPmw  : public QThread
{
    Q_OBJECT
public:
    explicit GpioPmw(QObject *parent = 0);
    
signals:

private:
   int m_fd;
   int m_sleep;
public:
    void startrun(QString gpioadress);
    void SetIntal(int intral);
    void run();
    
public slots:
    
};

#endif // GPIOPMW_H
