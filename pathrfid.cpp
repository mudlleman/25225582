#include "pathrfid.h"
#include "qdebug.h"

PathRfid::PathRfid(QObject *parent) :
    QObject(parent)
{
    QString comname="/dev/ttySP3";

    //  QString comname="/dev/ttyS1";
    // QString comname="ttyS0";
    m_serial =new xsserial(this);
    m_serial->Open(comname,9600);
    connect(&m_threadTime ,SIGNAL(TimeoutEvent()),this,SLOT(GetReadValue()));
    m_threadTime.startrun(80);
}
QString qreadstr="";
void PathRfid::GetReadValue()
{
    QString tempstr="$E0000000000000807D#";
    QString tempstr1="$E00000000000001571#";
    QString tempstr2="$E00000000000000277#$";

  //  qDebug()<<tempstr2;
    char *m_c="123456";
   m_serial->serial_write( m_c,6);
    int readlen=m_serial->serial_read();
     // qDebug()<<"readlen"<<readlen;
    // int readlen=32;
    if(readlen>0)
    {

        QString str= QString::fromUtf8(m_serial->uart_buff,readlen);
        qreadstr+=str;
       //  qDebug()<<qreadstr;
        if(qreadstr.length()>=tempstr.length())
        {
            int index=qreadstr.indexOf("$E");
            if(index>-1)
            {
                if(qreadstr.length()>=index+tempstr1.length())
                {
                    QString id=qreadstr.mid(index+2,tempstr1.length()-5);
                    int intid=id.toInt();
                    //qDebug()<<"id"<<intid;
                    // qDebug()<<“id”<<intid;
                    emit readidsingal(intid);
                }
            }
            qreadstr="";
        }

    }
}
