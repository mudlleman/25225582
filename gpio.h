#ifndef GPIO_H
#define GPIO_H
#include     <stdio.h>
#include     <stdlib.h>
#include     <unistd.h>
#include     <sys/types.h>
#include     <sys/stat.h>
#include     <fcntl.h>
#include     <termios.h>
#include     <errno.h>

#include<sys/ioctl.h>   /* using ioctl()         */
#include <QObject>

class Gpio : public QObject
{
    Q_OBJECT
public:
    explicit Gpio(QObject *parent = 0);
    bool  GetGpio(QString adress);
    void  SetGpio(QString adress,bool bvalue);
    bool  GetCheckGpio();    
    double GetAdc();
    bool getRcontrol();

    bool runorstopgpio();
private:
    bool m_canstart;
private:

signals:
    
public slots:
    
};

#endif // GPIO_H
