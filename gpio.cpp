#include "gpio.h"
#include <QDebug>
#include <QList>

Gpio::Gpio(QObject *parent) :
    QObject(parent)
{
    m_canstart=true;
   // m_canstart=false;
}
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

bool Gpio::GetGpio(QString adress)
{
    QByteArray ba = adress.toLatin1();
    char *dev = ba.data();
    char value;
    int fd;
    fd = open(dev, O_RDWR);
    if (fd < 0) {
        qDebug()<<adress;
        return false;
    }
    lseek(fd, 0, SEEK_SET);
    read(fd, &value, 1);
    close(fd);
    //qDebug()<<"value"<<value;
    if(value=='1')
    {
        return true;
    }
    if(value=='0')
    {
        return false;
    }
}
bool Gpio::GetCheckGpio()
{
     SetGpio("/sys/class/gpio/gpio116/value",false);
    QList<QString> devlist;
    QList<bool>    devbool;
    devlist.append("/sys/class/gpio/gpio69/value");
    devbool.append(true);
    devlist.append("/sys/class/gpio/gpio71/value");
    devbool.append(true);
    bool rb=false;
    for(int i=0;i<devlist.size();i++)
    {
        QString dev=devlist[i];
        bool bv=GetGpio(dev);

        if(bv!=devbool[i])
        {
            SetGpio("/sys/class/gpio/gpio116/value",true);
            return false;
        }
    }
    runorstopgpio();
    getRcontrol();
    if(!m_canstart)
    {
        return false;
    }

    return true;
}
//取电池电量
double Gpio::GetAdc()
{
    int fd;
    int iRes;
    int time = 100;
    double val;
    fd = open("/dev/magic-adc", 0);
    if(fd < 0){
        printf("open error by APP- %d\n",fd);
        close(fd);
        return 0;
    }
    ioctl(fd, 20, &iRes);			/* 开启除2     CH0    */
    val = (iRes * 3.7) / 4096.0;
    close(fd);
    return val;
}
bool tempykqvalue=true;
//遥控器控制
bool Gpio::getRcontrol()
{

    QString rcontrolgpioadress="/sys/class/gpio/gpio68/value";
    bool bv= GetGpio(rcontrolgpioadress);
    if(bv!=tempykqvalue)
    {
        if(bv==false)
        {
             m_canstart=!m_canstart;
        }
       // qDebug()<<m_canstart    ;
        tempykqvalue=bv;

    }

    return true;

}

bool Gpio::runorstopgpio()
{
   //开始按钮
    QString rcontrolgpioadress="/sys/class/gpio/gpio50/value";
    bool bv= GetGpio(rcontrolgpioadress);
   // qDebug()<<bv;
    if(bv!=true)
    {
        m_canstart=true;
    }
    else
    {

    }

    //停止按钮
    rcontrolgpioadress="/sys/class/gpio/gpio49/value";
    bv= GetGpio(rcontrolgpioadress);
    if(bv!=true)
    {
        m_canstart=false;
    }
    return true;
}
