#define nvdebu 1
#include "getnavigation.h"
#include <qdebug.h>





GetNavigation::GetNavigation(QObject *parent) :
    QObject(parent)
{

    nvalue1=-1000;
    nvalue2=-1000;
    m_canturn=false;
    nvwidth=7;
    m_trunleft=false;
    m_jointrrun=false;
    m_joindtwopath=false;
    m_directsmall=true;

}





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
            }
        }
    }
    GetTwoPathDirect(listnvstruct,oldlistnvstruct,&m_directsmall);
    oldlistnvstruct.clear();

    for(int i=0;i<listnvstruct.size();i++)
    {
        oldlistnvstruct.append(listnvstruct[i]);
    }

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

float GetNavigation::GetNavigationValue()
{
    return nvalue1;
}
