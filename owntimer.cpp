#include "owntimer.h"

OWNTimer::OWNTimer(QObject *parent) :
    QThread(parent)
{
}
void OWNTimer::startrun(int intral)
{
    b_run=true;
    m_intral=intral;
    start(HighestPriority);
}
void OWNTimer::stop()
{
    b_run=false;
}
void OWNTimer::SetIntal(int intral)
{
    m_intral=intral;
}
void OWNTimer::mmsleep(long ltime)
{
    msleep(ltime);
}

void OWNTimer::run()
{
     while (b_run)
     {
         msleep(m_intral);
         emit TimeoutEvent();
     }

}
