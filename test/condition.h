#ifndef CONDITION_H
#define CONDITION_H

#include <QObject>
#include<QtXml>
enum Sensortyp{EMIO,EMIA,EMSPEED};
//#include "controlcenter.h"

struct sonecondtions{
    QString ctype;
    QString name;
    QString CP;
    float cpvalue;
    int address;
    int id;
};
struct groupcondtion
{
    QList<sonecondtions> conditionlist;
    bool relationshipadn;
    int groupid;
};
typedef QMap<int, groupcondtion> groupcondtionMap;
class condition : public QObject
{
    Q_OBJECT
public:
    explicit condition(QObject *parent = 0);
public:
    groupcondtionMap mapcondition;
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
