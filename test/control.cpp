#include "control.h"

control::control(QObject *parent) :
    QObject(parent)
{
    //m_controlcenter="";
    openFile();
}
void control::openFile()
{
    QString fileName="xml/control.xml";
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

void control::GetCondtion(QDomElement& docElem)
{
    groupcontrol * tempgroup;
    QDomNode node = docElem.firstChild();

    while(!node.isNull())
    {
        QDomElement element = node.toElement(); // try to convert the node to an element.

        if(element.tagName()=="controlgroup")
        {
            groupcontrol gpcondition;
            tempgroup=&gpcondition;           
            if( element.hasAttribute("id") )
                tempgroup->groupid= element.attributeNode("id").value().toInt();          
            mapcontrol.insert(gpcondition.groupid,gpcondition);
        }

        if( element.tagName()=="control" )
        {
            // <condtion id="1" type="gpio" CP="=" name="test" cpvalue="" address="" />
            Scontrol cd;
            if( element.hasAttribute("id") )
                cd.id= element.attributeNode("id").value().toInt();
            if( element.hasAttribute("type") )
                cd.ctype= element.attributeNode("type").value();           
            if( element.hasAttribute("name") )
                cd.name= element.attributeNode("name").value();
            if( element.hasAttribute("setvalue") )
                cd.setvalue= element.attributeNode("setvalue").value().toFloat();
            if( element.hasAttribute("address") )
                cd.address= element.attributeNode("address").value().toInt();
            if( docElem.hasAttribute("id") )
            {
                int idd= docElem.attributeNode("id").value().toInt();
                QMap<int, groupcontrol>::iterator it;
                it = mapcontrol.find(idd);
                if(it!=mapcontrol.end())
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
