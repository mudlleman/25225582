#ifndef OWNTIMER_H
#define OWNTIMER_H

#include <QThread>

class OWNTimer : public QThread
{
    Q_OBJECT
public:
    explicit OWNTimer(QObject *parent = 0);
    
signals:
        void TimeoutEvent();

private:
    bool b_run;
    int m_intral;

 public:
    void startrun(int intral);
    void stop();
    void SetIntal(int intral);
    void mmsleep(long ltime);
    void run();

public slots:
    
};

#endif // OWNTIMER_H
