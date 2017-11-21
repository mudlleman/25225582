#define nvdebu 1
#include "getnavigation.h"
#include <qdebug.h>

const unsigned char auchCRCHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40};
const unsigned char auchCRCLo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
    0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
    0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
    0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
    0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
    0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
    0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
    0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
    0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80, 0x40};
unsigned short CRC16(char *puchMsg, unsigned short usDataLen)
{
    unsigned char uchCRCHi = 0xFF ;
    unsigned char uchCRCLo = 0xFF ;
    unsigned uIndex;
    while (usDataLen--)
    {
        uIndex = uchCRCHi ^ *puchMsg++ ;
        uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
        uchCRCLo = auchCRCLo[uIndex];
    }
    return (uchCRCHi << 8 | uchCRCLo) ;
}




GetNavigation::GetNavigation(QObject *parent) :
    QObject(parent)
{
    QString comname="/dev/ttySP4";

    //  QString comname="/dev/ttyS1";
    // QString comname="ttyS0";
    m_serial =new xsserial(this);
    m_serial->Open(comname,9600);
    connect(&m_threadTime ,SIGNAL(TimeoutEvent()),this,SLOT(GetReadValue()));
    m_threadTime.startrun(50);
    nvalue1=-1000;
    nvalue2=-1000;
    m_canturn=false;
    nvwidth=7;
    m_trunleft=false;
    m_jointrrun=false;
    m_joindtwopath=false;
    m_directsmall=true;

}
int tempgetno=0;

int allno=0;
int chenggo=0;
void GetNavigation::GetReadValue()
{

    unsigned char WillSendValue[8];

    //02 03 00 02 00 02 65 F8

    WillSendValue[0]=0x02;
    WillSendValue[1]=0x03;
    WillSendValue[2]=0x00;
    WillSendValue[3]=0x02;
    WillSendValue[4]=0x00;
    WillSendValue[5]=0x02;

    WillSendValue[6]=0x65;
    WillSendValue[7]=0xF8;

    allno++;

    m_serial->serial_write((char*)WillSendValue,8);
    m_threadTime.mmsleep(40);
    int readlen=m_serial->serial_read();
    //  qDebug()<<"l"<<readlen;
    if(tempgetno>10)
    {
        // nvalue1=-2000;
    }
    QVector<uchar> qu;
    for(int i=0;i<readlen;i++)
    {
        qu.append(m_serial->uart_buff[i]);
    }

    if(readlen==8)
    {
        char tempchar[8];
        for(int i=0;i<8;i++)
        {
            tempchar[i]=m_serial->uart_buff[i];
        }
        m_serial->uart_buff[4]=0;
        for(int i=5;i<9;i++)
        {
            m_serial->uart_buff[i]=tempchar[i-1];
        }
        readlen=9;
    }

    //   qDebug()<<qu;
    if(readlen==9)
    {


        char sendchar[7];

        for(int i=0;i<7;i++)
        {
            sendchar[i]=m_serial->uart_buff[i];

        }
        unsigned short crc= CRC16(sendchar,7);
        unsigned char cch=crc>>8;
        unsigned char ccl=crc;
        //  qDebug()<<cch<<"l"<<ccl;

        unsigned char uch=(unsigned char)m_serial->uart_buff[7];
        unsigned char ucl=(unsigned char)m_serial->uart_buff[8];




        if(cch==uch&&ccl==ucl)
        {
            chenggo++;
            //  qDebug()<<"cg"<<chenggo<<"all"<<allno;
            nvalue1=-2000;
            unsigned char b1=m_serial->uart_buff[5];
            unsigned char b2=m_serial->uart_buff[6];
            //qDebug()<<cch<<"lqqqq"<<ccl;
            b1=~b1;
            b2=~b2;

            QString qsb1=QString::number(b1,10);
            QString qsb2=QString::number(b2,10);

            //  QString sendstr="navigation "+qsb1+" "+qsb2;
            // QByteArray cstr = sendstr.toAscii();
            // m_ludp.sendata(cstr);

            Transition(b2,b1);
        }

    }

}

int oldvalue=0;
QList<nvstrcut> oldlistnvstruct;
void GetNavigation::Transition( int b1, int b2)
{


    int vl = b1 + (b2 << 8);


    QList<nvstrcut> listnvstruct;


    int allnubmer=0;
    float numuber = 0;
    for(int i=0;i<16;i++)
    {
        int temppy = 1 << i;
        int tempi = (temppy) & vl;

        if (tempi > 0)
        {
            numuber++;
            allnubmer++;
        }
        if(tempi==0)
        {
            if (numuber>0)
            {

                nvstrcut nvstrck;
                nvstrck.endno=i-1;
                nvstrck.startno=i-numuber;
                nvstrck.number=numuber;
                listnvstruct.append(nvstrck);
                //lnvstrcut.lnvstrcut.append(nvstrck);
                // qDebug()<<"number"<<numuber<<"endno"<<i-1;
            }
            numuber = 0;

        }
        if(i==15)
        {
            if (numuber > 0)
            {
                nvstrcut nvstrck;
                nvstrck.endno=i;
                nvstrck.number=numuber;
                nvstrck.startno=i-numuber;
                listnvstruct.append(nvstrck);
                //lnvstrcut.lnvstrcut.append(nvstrck);
            }
        }
    }

    /*
    m_begintrun=false;
    if(allnubmer>nvwidth&&allnubmer>oldvalue&&listnvstruct.size()==1)
    {
        m_begintrun=true;
        if(m_canturn)
        {
            m_directsmall=false;
        }

    }
    if(m_begintrun&&listnvstruct.size()>1)
    {
        m_jointrrun=true;
    }
    if(m_jointrrun&&listnvstruct.size()==1&&allnubmer<=nvwidth)
    {
        m_begintrun=false;
        m_jointrrun=false;
        m_directsmall=true;
        m_canturn=false;
    }


    if(!m_begintrun&&!m_jointrrun)
    {
        if(!m_joindtwopath&&allnubmer>oldvalue&&listnvstruct.size()>1)
        {
            GetTwoPathDirect(listnvstruct,oldlistnvstruct,&m_begintrun);
            m_joindtwopath=true;
        }
    }
    if(m_joindtwopath&&listnvstruct.size()==1&&allnubmer<=nvwidth)
    {
        m_joindtwopath=false;
        m_directsmall=true;
    }*/

    GetTwoPathDirect(listnvstruct,oldlistnvstruct,&m_directsmall);
    oldlistnvstruct.clear();

    for(int i=0;i<listnvstruct.size();i++)
    {
        oldlistnvstruct.append(listnvstruct[i]);
    }
    oldvalue=allnubmer;

    nvalue1=GetNvflaotvalue(listnvstruct,m_directsmall);


    // qDebug()<<"nvallnumber"<<nvalue1;



}
float GetNavigation::GetNvflaotvalue(QList<nvstrcut> curlist,bool directsmall)
{
    float nvfloat=-10000;
    if(curlist.size()==0)
        return nvfloat;
    if(directsmall)
    {
        int tempsamll=10000;
        nvstrcut strcutnv;
        for(int i=0;i<curlist.size();i++)
        {
            nvstrcut tempstrcut=curlist[i];
            if(tempstrcut.startno<tempsamll)
            {
                tempsamll=tempstrcut.startno;
                strcutnv=curlist[i];
            }
        }
        int points=nvwidth;
        if(strcutnv.number<nvwidth)
        {
            points=strcutnv.number;
        }
        nvfloat=pointtofloat(strcutnv.startno,points);
    }
    else
    {
        int tempsamll=0;
        nvstrcut strcutnv;
        for(int i=0;i<curlist.size();i++)
        {
            nvstrcut tempstrcut=curlist[i];
            if(tempstrcut.endno>tempsamll)
            {
                tempsamll=tempstrcut.endno;
                strcutnv=curlist[i];
            }
        }
        int points=nvwidth;
        if(strcutnv.number<nvwidth)
        {
            points=strcutnv.number;
        }
        int starttemp=strcutnv.endno-points+1;
        nvfloat=pointtofloat(starttemp,points);
    }
    return nvfloat;
}
float GetNavigation::pointtofloat(int srart, int len)
{
    // qDebug()<<"start"<<srart<<"len"<<len;
    float turenumber=0;
    for(int i=srart;i<srart+len;i++)
    {
        turenumber+=i;
    }
    //    qDebug()<<"turenumber"<<turenumber;
    turenumber = turenumber / len;
    turenumber = turenumber / 15 * 150-75;
    return turenumber;
}

bool GetNavigation::GetTwoPathDirect(QList<nvstrcut> curlist, QList<nvstrcut> oldlist,bool *directsmall)
{
    if(oldlist.size()==1&&curlist.size()>1)
    {
        nvstrcut nt= oldlist[0];
        if(nt.number>nvwidth+1)
        {
            return false;
        }
        int oldstart=nt.startno;
        int temp=0;
        int newpathx=-1;
        for(int i=0;i<curlist.size();i++)
        {
            nvstrcut temsct=curlist[i];
            int startv=temsct.startno;
            int cha=qAbs(startv-oldstart);
            if(cha>temp)
            {
                temp=cha;
                newpathx=startv;
            }
        }

        if(newpathx>=oldstart)
        {
            *directsmall=true;
        }
        else
        {
            *directsmall=false;
        }
        qDebug()<<oldstart<<"new:"<<newpathx<<"b:"<<*directsmall;


    }
}
void GetNavigation::SetCanTurn(bool direct)
{
    //  m_directsmall=~direct;

    if(direct)
    {
        m_directsmall=false;
    }
    else
    {
        m_directsmall=true;
    }
    qDebug()<<"samll"<<m_directsmall;
}

float GetNavigation::GetNavigationValue(int mtype)
{
    return nvalue1;
}
