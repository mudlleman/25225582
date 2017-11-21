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
                cd.address= element.attributeNode("address").value().toInt();
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
