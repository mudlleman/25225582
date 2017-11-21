#include "madacontrol.h"
#include <QDebug>
#include <QMutex>
QMutex mutex;
MadaControl::MadaControl(QString comname,QObject *parent) :
    QThread(parent)
{
    // QString comname="/dev/ttySP1";
    m_comname=comname;
    //qbtyeSation.clear();
    m_serial =new xsserial(this);
    m_serial->Open(comname,9600);
    m_postion=0;
    m_bjpostion=0;
    m_willrunstep=0;

    m_turnspeed=130;

    temppostion=0;
    setpostion=0;

    isusenow=false;
    nowtrun=false;

    QByteArray qbyte;
    uchar send[7]={183,184,1,10,1,5,128};
    for(int i=0;i<7;i++)
    {
        qbyte.append(send[i]);
    }
    wirtedata(qbyte);
    start();
}
void MadaControl::run()
{
    while(1)
    {
        msleep(50);
        GetReadValue();
    }
}

int readno=0;
int readcg=0;


void MadaControl::GetReadValue()
{

    readno++;
    int readlen=m_serial->serial_read();

    if(readlen>0)
    {


        for(int i=0;i<readlen;i++)
        {
            m_tempcharv.append((unsigned char)m_serial->uart_buff[i]);
        }

        if(m_tempcharv.size()<22)
        {
            return;
        }
        //
        unsigned char bjz[4]={184,183,1,193};
        int findindex=-1;
        int datalen=22;
        for(int i=0;i<m_tempcharv.size()-4;i++)
        {
            unsigned char uc0=m_tempcharv.at(i);
            unsigned char uc1=m_tempcharv.at(i+1);
            unsigned char uc2=m_tempcharv.at(i+2);
            unsigned char uc3=m_tempcharv.at(i+3);
            if(uc0==bjz[0]&&uc1==bjz[1]&&uc2==bjz[2]&&uc3==bjz[3])
            {                
                findindex=i;
                break;
            }
        }
        if(findindex>-1)
        {
            if(m_tempcharv.size()>=(findindex+datalen))
            {

                readcg++;
                int indexdata=15+findindex;
                int addr = m_tempcharv.at(indexdata) & 0xFF;
                addr |= ((m_tempcharv.at(indexdata+1)<< 8) & 0xFF00);
                addr |= ((m_tempcharv.at(indexdata+2) << 16) & 0xFF0000);
                addr |= ((m_tempcharv.at(indexdata+3)<< 24) & 0xFF000000);

                m_listpostion.push_front(addr);

                indexdata=5+findindex;
                addr = m_tempcharv.at(indexdata) & 0xFF;
                addr |= ((m_tempcharv.at(indexdata+1)<< 8) & 0xFF00);
                 int speed=qAbs(addr);
                if(addr>20000)
                {
                    speed=qAbs(65535-addr);
                }
             //   qDebug()<<m_comname<<m_listpostion.at(0)<<speed;
                if(m_listpostion.size()==3)
                {
                    int p1=m_listpostion.at(0);
                    int p2=m_listpostion.at(1);
                    int p3=m_listpostion.at(2);
                    int pp=(p1+p3)/2;
                    if(qAbs(pp-p2)<500&&qAbs(speed)<3000)
                    {

                        m_postion=p3;
                    }
                    else
                    {
                        m_listpostion.clear();
                        return;
                    }
                    m_listpostion.pop_back();
                }

                //  qDebug()<<"speed"<<speed<<m_postion;
                //  qDebug()<<m_comname<<"cg"<<readcg<<readno<<readlen<<findindex<<qba.size()<<addr;

                m_tempcharv.clear();
                if(nowtrun)
                {
                    if(setpostion==0)
                    {
                        setpostion=m_postion;

                    }
                    int wrunspeed=m_turnspeed;
                    if(m_willrunstep<0)
                    {
                        wrunspeed=0-m_turnspeed;
                    }
                   // qDebug()<<m_comname<<"start"<<m_postion;
                    temppostion++;
                    QByteArray qSation= ctbyte.GetSpeedByte(1,wrunspeed);
                    m_serial->serial_write(qSation.data(),qSation.length());

                }
                if(isusenow&&setpostion!=0)
                {
                    if(qAbs(setpostion-m_postion)>=(qAbs(m_willrunstep)-1)&&temppostion>15)
                    {
                        qDebug()<<m_comname<< "old"<<setpostion<<"new"<<m_postion<<m_willrunstep<<qAbs(setpostion-m_postion);
                        qDebug()<<m_comname<<"zwwc";
                        nowtrun=false;
                        if(speed!=0)
                        {
                            QByteArray stopba  = ctbyte.GetSpeedByte(1,0);
                            m_serial->serial_write(stopba.data(),stopba.length());
                        }
                        else
                        {
                            temppostion=0;
                            isusenow=false;
                        }
                    }
                }

                // qDebug()<<m_postion;
                //  qDebug()<<m_tempcharv;
            }
        }
        // }
        if(m_tempcharv.size()>45)
        {
            m_tempcharv.clear();
        }
    }
}
void MadaControl::setcurpostion(int bjpostion)
{
    m_bjpostion=m_postion;
    qDebug()<<"m_bjpostion"<<m_bjpostion;
}
int MadaControl::getpostion()
{
    return qAbs(m_postion-m_bjpostion);
}

void MadaControl::MadaRunType(int type)
{

}


void MadaControl::controlstep(int steplen)
{
    mutex.lock();
    qDebug()<<steplen;
    m_willrunstep=steplen;
    isusenow=true;
    temppostion=0;
    setpostion=0;
    nowtrun=true;
    mutex.unlock();

}
void MadaControl::wirtedata(QByteArray qb)
{
    if(!isusenow)
    {
      //  qDebug()<<"write"<<m_comname;
        char *data=qb.data();
        m_serial->serial_write(data,qb.length());
    }
}
