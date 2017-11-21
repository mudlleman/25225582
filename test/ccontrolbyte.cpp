#include "ccontrolbyte.h"

CcontrolByte::CcontrolByte(QObject *parent) :
    QObject(parent)
{
}
QByteArray CcontrolByte::
QByteArray CcontrolByte::GetSpeedByte(int madindex,int speed)
{
    QByteArray qbyte;
    uchar send[8]={183,184,1,130,2};
    send[2] =(uchar)madindex;
    short tempspeed=speed;

    uchar bb1= (uchar)  (0x000000ff & tempspeed);
    uchar bb2= (uchar) ((0x0000ff00 & tempspeed) >> 8);
    send[5]=bb1;
    send[6]=bb2;
    uchar check=0;
    for(int i=0;i<7;i++)
    {
        check=check+send[i];
    }
    send[7]=(uchar)(256-check);
    qbyte.append((char*)send,8);

 //   b1
    return qbyte;
}
