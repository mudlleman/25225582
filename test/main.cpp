#include <QtGui/QApplication>
#include "mainwindow.h"
#include "ccontrolbyte.h"
#include <QDebug>
#include "form.h"
#include "readpath.h"
#include "condition.h"
#include "control.h"
#include "work.h"
#include "formudp.h"

QString qreadstr="$E0000000000000807D#";
void GetReadValue()
{
    QString tempstr="$E0000000000000807D#";
    QString tempstr1="$E00000000000001571#";
    QString tempstr2="$E00000000000000277#$";
    //int readlen=m_serial->serial_read();
    int readlen=32;
    if(readlen>0)
    {
        //  QString str(m_serial->uart_buff,readlen);
        QString str="";
        qreadstr+=str;
        if(qreadstr.length()>=tempstr.length())
        {
            int index=qreadstr.indexOf("$E");
            if(index>-1)
            {
                if(qreadstr.length()>=index+tempstr1.length())
                {
                    QString id=qreadstr.mid(index+2,tempstr1.length()-5);
                    int intid=id.toInt();
                    // emit readidsingal(intid);
                    // QString bb="asf";
                }
            }
            qreadstr="";

        }
        // str.indexOf()
    }
}

void GetSpeedByte(int madindex,int speed)
{
    QByteArray qbyte;
    uchar send[12]={183,184,2,220,6,1,1,0,0,0,0,171};
    send[2] =(uchar)madindex;
    int tempspeed=speed;

    uchar bb1= (uchar)  (0x000000ff & tempspeed);
    uchar bb2= (uchar) ((0x0000ff00 & tempspeed) >> 8);
    uchar bb3= (uchar) ((0x00ff0000 & tempspeed) >> 16);
    uchar bb4= (uchar) ((0xff000000 & tempspeed) >> 24);
    send[5]=bb1;
    send[6]=bb2;

    send[7]=bb3;
    send[8]=bb4;

    uchar check=0;
    for(int i=0;i<11;i++)
    {
        check=check+send[i];
    }
    send[11]=(uchar)(256-check);
     for(int i=0;i<12;i++)
     {
         qDebug()<<send[i];
     }

    //   qbyte.append((char*)send,8);

 //   b1
   // return qbyte;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Form w;
    w.show();
    GetReadValue();

    GetSpeedByte(2,-257);

    FormUdp dd;

    int d=100;
    QString bbs="aaaa";
    QString dasd=bbs+QString::number(d, 10); ;

    short i=-1000;

    uchar bb1= (uchar)  (0x000000ff & i);
    uchar bb2= (uchar) ((0x0000ff00 & i) >> 8);

    CcontrolByte cb;
    QByteArray qba= cb.GetSpeedByte(1,1000);
    qDebug()<<qba;

    QString qstr="2-3-4";

    QStringList qlist= qstr.split("-");

    QString st=qlist.at(0);

    work wk;
    control cl;

    condition cd;
    ReadPath rp;



    QString tempstr="$E00000000000005277#$E00000000000000277#";
    QString tempstr1="#$E00000000000000277#";
    QString tempstr2="$E00000000000000277#$";

    int index=tempstr.indexOf("$E");

    if(tempstr.length()>index+tempstr1.length())
    {
        QString id=tempstr.mid(index+2,tempstr1.length()-6);
        int intid=id.toInt();
        QString bb="asf";
    }
    QVector<int> qv;
    qv.append(1);
    qv.append(2);
    qv.append(3);
    qv.pop_front();
    qDebug()<<qv[qv.size()-1];

   // tempstr.mid()




    return a.exec();
}

