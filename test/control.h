#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include<QtXml>

struct Scontrol{
    QString ctype;
    QString name;
    float setvalue;
    int address;
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
