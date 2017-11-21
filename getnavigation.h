#ifndef GETNAVIGATION_H
#define GETNAVIGATION_H

#include "owntimer.h"
#include "xsserial.h"
#include <QVector>
#include "ludp.h"

struct nvstrcut
{
    int endno;
    int startno;
    int number;
};
struct listnv
{
     QVector<nvstrcut> lnvstrcut;
};

class GetNavigation : public QObject
{
  //  enum  Direectenum { front, back, left,right};
    Q_OBJECT
public:
    explicit GetNavigation(QObject *parent = 0);
     float GetNavigationValue(int mtype);
     void SetCanTurn(bool direct);
private:
    OWNTimer m_threadTime;
    xsserial *m_serial;
    int nvwidth;
    float nvalue1,nvalue2;
    QVector <int> nvallnumber;
    QVector<listnv> m_listnv;
    ludp m_ludp;
    bool m_canturn;
    bool m_trunleft;

    bool m_begintrun;
    bool m_jointrrun;
    bool m_outrun;

    bool m_joindtwopath;
    bool m_outtwopath;
    bool m_directsmall;

private :
    void Transition(int b1,int b2);
    bool GetTwoPathDirect(QList<nvstrcut> curlist,QList<nvstrcut> oldlist,bool *directsmall);
    float GetNvflaotvalue(QList<nvstrcut> curlist,bool directsmall);
    float pointtofloat(int srart,int len);
public:
signals:
    void NavigationChangeEvent(float nv);
private slots:
      void GetReadValue();
    
};

#endif // GETNAVIGATION_H
