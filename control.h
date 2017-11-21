#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include<QtXml>
#include "gpio.h"
#include "madacontrol.h"
#include "owntimer.h"
struct Scontrol{
    QString ctype;
    QString name;
    float setvalue;
    QString address;
    int id;
};
struct groupcontrol
{
    QList<Scontrol> conditionlist;
    int groupid;
};
typedef QMap<int, groupcontrol> groupcontrolMap;
class control : public QObject
{
    Q_OBJECT
public:
    explicit control(QObject *parent = 0);
public:
    groupcontrolMap mapcontrol;
    void execute(int controlID);
    void SetControlface(float *speed, Gpio *gpio, MadaControl *madact1,MadaControl *madact2);
private:
    //ControlCenter *m_controlcenter;
    MadaControl *m_madact1;
    MadaControl *m_madact2;
    Gpio *m_gpio;
    float * m_speed;
     OWNTimer m_threadTime;
private :
    void openFile();
    void GetCondtion(QDomElement& docElem);
    void controlgpio(QString adress,float value);
    //checktyp ck;
signals:
    
public slots:
    
};

#endif // CONDITION_H
