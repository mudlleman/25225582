#ifndef WORK_H
#define WORK_H

#include <QObject>
#include<QtXml>
#include "condition.h"
#include "control.h"
#include <QThread>
struct workstep{
    QString condtiongroup;
    QString controlgroup;
    int id;
};
struct workgroup
{
    QList<workstep> conditionlist;
    QString groupid;
};
typedef QMap<QString, workgroup> workMap;
class work : public QThread
{
    Q_OBJECT
public:
    explicit work(QObject *parent = 0);
    void executework(QString workid);
    void setinterface(control *ct,condition *cd );
    void run();
public:
    workMap mapwork;
private:
    //ControlCenter *m_controlcenter;
    control *m_control;
    condition *m_conditon;
    QString m_workid;
private :
    void openFile();
    void GetCondtion(QDomElement& docElem);
    //checktyp ck;
signals:
    
public slots:
    
};

#endif // CONDITION_H
