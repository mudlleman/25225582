#include <QtGui/QApplication>
#include "mainwindow.h"
#include "controlcenter.h"
#include "QDebug"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

 //   qDebug()<<"start";
   // work mywork;
   // mywork.executework("7");

 /*  QList<PointRuntype> m_qlistpasspath;
    ReadPath m_readpath;

    m_qlistpasspath=m_readpath.GetPath(9,7,6);

    qDebug()<<m_qlistpasspath.length();
    for(int i=0;i<m_qlistpasspath.size();i++)
    {
        PointRuntype prtype=m_qlistpasspath[i];
        qDebug()<<"id"<<prtype.pathid<<"right"<<prtype.isright<<prtype.topathid;
    }
*/
    ControlCenter CC;
/*
    MadaControl *m_madacontrol1=  new MadaControl("/dev/ttySP0");

    int mm=0;

    while(true)
    {
        if(mm%2==0)
        {
            m_madacontrol1->controlstep(500);
        }
        else
        {
            m_madacontrol1->controlstep(-500);
        }
        mm++;
        sleep(13);
    }

*/

    MainWindow w;
    w.show();
    
    return a.exec();
}
