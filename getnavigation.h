#ifndef GETNAVIGATION_H
#define GETNAVIGATION_H


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
     float GetNavigationValue();
     void SetCanTurn(bool direct);
     void Transition(int b1,int b2);
private:

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

    bool GetTwoPathDirect(QList<nvstrcut> curlist,QList<nvstrcut> oldlist,bool *directsmall);
    float GetNvflaotvalue(QList<nvstrcut> curlist,bool directsmall);
    float pointtofloat(int srart,int len);
public:
signals:
    //void NavigationChangeEvent(float nv);
private slots:

    
};

#endif // GETNAVIGATION_H
