#include "condition.h"

condition::condition(QObject *parent) :
    QObject(parent)
{
    //m_controlcenter="";
    openFile();
}
void condition::openFile()
{
    QString fileName="xml/condtion.xml";
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QDomDocument dom("WCM");
        if (dom.setContent(&file))
        {

            QDomElement docElem = dom.documentElement();
            GetCondtion(docElem);
        }
    }
    file.close();
}
bool condition::GetGpioStat(QString adress, int bjvalue)
{

    sleep(1);
    bool bj=false;
    if(bjvalue==1)
    {
        bj=true;
    }
    QString rcontrolgpioadress="/sys/class/gpio/gpio"+adress+"/value";
       // QString rcontrolgpioadress="/sys/class/gpio/gpio68/value";
    bool gpiovalue= m_gpio->GetGpio(rcontrolgpioadress);
   //  qDebug()<<"condtion"<<adress<<gpiovalue;
    if(gpiovalue==bj)
    {
        return true;
    }
     // qDebug()<<adress<<gpiovalue<<bjvalue;
    return false;
}
void condition::SetControlface(float *speed, Gpio *gpio, MadaControl *madact1, MadaControl *madact2)
{
    m_speed=speed;
    m_gpio=gpio;
    m_madact1=madact1;
    m_madact2=madact2;
}

bool condition::GetMapConndtion(int mapid)
{
     qDebug()<<222222;
    QMap<int, groupcondtion>::iterator it;
    it = mapcondition.find(mapid);

    bool breturn=true;
    if(it!=mapcondition.end())
    {
        QList<sonecondtions> sds= it.value().conditionlist;
        bool band= it.value().relationshipadn;
        bool bwhile= it.value().whilecheck;
        while(true)
        {
             breturn=true;
            for(int i=0;i<sds.size();i++)
            {
                sonecondtions cd=sds[i];
                if(cd.ctype=="gpio")
                {
                    bool bgetvalue=GetGpioStat(cd.address,cd.cpvalue);

                    if(bgetvalue!=true&&band==true)
                    {
                        breturn=false;
                        break;
                    }
                    if(bgetvalue&&band==false)
                    {
                        breturn=true;
                        break;
                    }
                }
            }
           // qDebug()<<"bwhile"<<bwhile<<"breturn"<<breturn;
            if(bwhile&&breturn)
            {
                break;

            }
            if(!bwhile)
            {
                break;
            }
        }
    }
    return breturn;
}

void condition::GetCondtion(QDomElement& docElem)
{
    groupcondtion * tempgroup;
    QDomNode node = docElem.firstChild();

    while(!node.isNull())
    {
        QDomElement element = node.toElement(); // try to convert the node to an element.

        if(element.tagName()=="condtiongroup")
        {
            groupcondtion gpcondition;
            tempgroup=&gpcondition;
            tempgroup->relationshipadn=false;
            if( element.hasAttribute("id") )
                tempgroup->groupid= element.attributeNode("id").value().toInt();
            if( element.hasAttribute("relationshipadn") )
            {
                int tempint=element.attributeNode("relationshipadn").value().toInt();
                if(tempint==1)
                {
                    tempgroup->relationshipadn=true;
                }
            }
            tempgroup->whilecheck=false;
            if( element.hasAttribute("whilecheck") )
            {
                int tempint=element.attributeNode("whilecheck").value().toInt();
                if(tempint==1)
                {
                    tempgroup->whilecheck=true;
                }
            }
            mapcondition.insert(gpcondition.groupid,gpcondition);
        }

        if( element.tagName()=="condtion" )
        {
            // <condtion id="1" type="gpio" CP="=" name="test" cpvalue="" address="" />
            sonecondtions cd;
            if( element.hasAttribute("id") )
                cd.id= element.attributeNode("id").value().toInt();
            if( element.hasAttribute("type") )
                cd.ctype= element.attributeNode("type").value();
            if( element.hasAttribute("CP") )
                cd.CP= element.attributeNode("CP").value();
            if( element.hasAttribute("name") )
                cd.name= element.attributeNode("name").value();
            if( element.hasAttribute("cpvalue") )
                cd.cpvalue= element.attributeNode("cpvalue").value().toFloat();
            if( element.hasAttribute("address") )
                cd.address= element.attributeNode("address").value();
            if( docElem.hasAttribute("id") )
            {
                int idd= docElem.attributeNode("id").value().toInt();
                QMap<int, groupcondtion>::iterator it;
                it = mapcondition.find(idd);
                if(it!=mapcondition.end())
                {
                    it.value().conditionlist.append(cd);;
                }
            }
        }
        if( !element.isNull() )
        {
            GetCondtion(element);
        }
        node = node.nextSibling();
    }
    return;
}
