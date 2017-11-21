#include "getpathid.h"
GetPathID::GetPathID(QObject *parent) :
    QObject(parent)
{
    QString comname="/dev/ttySP0";

    //  QString comname="/dev/ttyS1";
    // QString comname="ttyS0";
    m_serial =new xsserial(this);
    m_serial->Open(comname,9600);
    connect(&m_threadTime ,SIGNAL(TimeoutEvent()),this,SLOT(GetReadValue()));
    m_threadTime.startrun(80);
}
QString qreadstr="";
void GetPathID::GetReadValue()
{
    QString tempstr="$E00000000000000277#$E00000000000000277#";
    QString tempstr1="#$E00000000000000277#";
    QString tempstr2="$E00000000000000277#$";
    int readlen=m_serial->serial_read();
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
                if(qreadstr.length()>index+tempstr1.length())
                {
                    QString id=qreadstr.mid(index+2,tempstr1.length()-6);
                    int intid=id.toInt();
                    //  emit readidsingal(intid);
                    // QString bb="asf";
                }
            }
            qreadstr="";

        }
        // str.indexOf()
    }
}
