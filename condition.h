#ifndef CONDITION_H
#define CONDITION_H

#include <QObject>
#include<QtXml>
#include "gpio.h"
#include "madacontrol.h"
enum Sensortyp{EMIO,EMIA,EMSPEED};
//#include "controlcenter.h"

struct sonecondtions{
    QString ctype;
    QString name;
    QString CP;
    float cpvalue;
    QString address;
    int id;
};
struct groupcondtion
{
    QList<sonecondtions> conditionlist;
    bool relationshipadn;
    int groupid;
    bool whilecheck;
};
typedef QMap<int, groupcondtion> groupcondtionMap;
class condition : public QObject
{
    Q_OBJECT
public:
    explicit condition(QObject *parent = 0);
public:
    groupcondtionMap mapcondition;
    bool GetMapConndtion(int mapid);
    void SetControlface(float *speed,Gpio *gpio, MadaControl *madact1, MadaControl *madac2);
private:
    //ControlCenter *m_controlcenter;
    Gpio *m_gpio;
    float *m_speed;
    MadaControl *m_madact1;
    MadaControl *m_madact2;

private :
    void openFile();
    void GetCondtion(QDomElement& docElem);
    bool GetGpioStat(QString adress,int bjvalue);
    //checktyp ck;
signals:
    
public slots:
    
};

#endif // CONDITION_H
