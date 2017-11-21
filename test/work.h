#ifndef WORK_H
#define WORK_H

#include <QObject>
#include<QtXml>

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
class work : public QObject
{
    Q_OBJECT
public:
    explicit work(QObject *parent = 0);
public:
    workMap mapwork;
private:
    //ControlCenter *m_controlcenter;
private :
    void openFile();
    void GetCondtion(QDomElement& docElem);
    //checktyp ck;
signals:
    
public slots:
    
};

#endif // CONDITION_H
