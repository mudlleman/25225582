#ifndef THREADTIMER_H
#define THREADTIMER_H


#include <QObject>
#include<QThread>
class ThreadTimer : public QThread
{

        Q_OBJECT
signals:
        void TimeoutEvent();

private:
    bool b_run;
    int m_intral;
public:ThreadTimer(QObject *parent = 0): QThread(parent)
        {
            b_run=true;
            m_intral=200;
        };
        void startrun(int intral)
        {
            m_intral=intral;
            start(HighestPriority);
        };
        void stop()
        {
            b_run=false;
        };
        void SetIntal(int intral)
        {
            m_intral=intral;
        };
        void mmsleep(long ltime)
        {
            msleep(ltime);
        };

    void run()
        {
             while (b_run)
             {
                 msleep(m_intral);
                 emit TimeoutEvent();
             }

        };
};

#endif // THREADTIMER_H
