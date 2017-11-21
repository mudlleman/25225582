#include "speedpulse.h"

SpeedPulse::SpeedPulse(QObject *parent) :
    QThread(parent)
{
}
void SpeedPulse::initvalue(long lvalue)
{
    m_pulse=lvalue;
}
long SpeedPulse::getpulsevalue()
{
    return m_pulse;
}

void SpeedPulse::run()
{
    QString adress="/sys/class/gpio/gpio69/value";
    QByteArray ba = adress.toLatin1();
    char *dev = ba.data();
    char value;
    char tempvalue=1;
    int fd;
    fd = open(dev, O_RDWR);
    if (fd < 0) {
        return ;
    }
    lseek(fd, 0, SEEK_SET);
    for(;;)
    {
        read(fd, &value, 1);
        if(tempvalue!=value)
        {
            m_pulse++;
            tempvalue=value;
        }
        msleep(3);
    }
    close(fd);
}
