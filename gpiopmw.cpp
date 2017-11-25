#include "gpiopmw.h"
#include "QDebug"

GpioPmw::GpioPmw(QObject *parent) :
   QThread(parent)
{
}
void GpioPmw::startrun(QString gpioadress)
{
    m_sleep=100;
    QByteArray ba = gpioadress.toLatin1();
    char *dev = ba.data();
    m_fd = open(dev, O_RDWR);
    if (m_fd < 0) {
        qDebug()<<gpioadress;
        return;
    }
     write(m_fd, "1", 0);
    start(HighestPriority);
}

void GpioPmw::SetIntal(int intral)
{
    if(intral>0&&intral<100)
    {
        m_sleep=intral;
    }

}
void GpioPmw::run()
{
    int bolen=100;
    while(1)
    {
         write(m_fd, "1", 1);
         msleep(m_sleep);
         write(m_fd, "0", 1);
         msleep(bolen-m_sleep);
    }
}

/*
void Gpio::SetGpio(QString adress, bool bvalue)
{

    QByteArray ba = adress.toLatin1();
    char *dev = ba.data();
    int fd;
    fd = open(dev, O_RDWR);
    if (fd < 0) {
        qDebug()<<adress;
        return;
    }
    if(bvalue)
    {
        write(fd, "1", 1);
    }
    else
    {
        write(fd, "0", 1);
    }
    close(fd);
}
*/
