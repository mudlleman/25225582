#include "ccontrolbyte.h"

CcontrolByte::CcontrolByte(QObject *parent) :
    QObject(parent)
{
}
QByteArray CcontrolByte::GetPostionByte(int madindex,int speed)
{
    QByteArray qbyte;
    uchar send[12]={183,184,2,220,6,1,1,0,0,130,0,171};
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
    qbyte.append((char*)send,12);
    return qbyte;
}

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
QByteArray CcontrolByte::GetStateOPen(int madindex, bool start)
{
    uchar send[7]={183,184,1,10,1,5,128};
    send[2]=madindex;
    send[5]=5;
    if(!start)
    {
        send[5]=5;
    }
    uchar check=0;
    for(int i=0;i<6;i++)
    {
        check=check+send[i];
    }
    send[6]=(uchar)(256-check);
    QByteArray qbyte;
    qbyte.append((char*)send,7);
    return qbyte;
}
