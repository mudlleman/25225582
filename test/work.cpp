#include "work.h"

work::work(QObject *parent) :
    QObject(parent)
{
    //m_controlcenter="";
    openFile();
}
void work::openFile()
{
    QString fileName="xml/work.xml";
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

void work::GetCondtion(QDomElement& docElem)
{

    QDomNode node = docElem.firstChild();

    while(!node.isNull())
    {
        QDomElement element = node.toElement(); // try to convert the node to an element.

        if(element.tagName()=="pathpoint")
        {
            workgroup gpcondition;

            QString qid="";
            if( element.hasAttribute("id") )
                qid+= element.attributeNode("id").value();
            if( element.hasAttribute("pointtype") )
                qid+= element.attributeNode("pointtype").value();
            gpcondition.groupid=qid;
            mapwork.insert(qid,gpcondition);
        }

        if( element.tagName()=="workstep" )
        {
            // <condtion id="1" type="gpio" CP="=" name="test" cpvalue="" address="" />
            workstep cd;
            if( element.hasAttribute("id") )
                cd.id= element.attributeNode("id").value().toInt();
            if( element.hasAttribute("condtiongroup") )
                cd.condtiongroup= element.attributeNode("condtiongroup").value();
            if( element.hasAttribute("controlgroup") )
                cd.controlgroup= element.attributeNode("controlgroup").value();


            QString qid="";
            if( docElem.hasAttribute("id") )
                qid+= docElem.attributeNode("id").value();
            if( docElem.hasAttribute("pointtype") )
                qid+= docElem.attributeNode("pointtype").value();
            QMap<QString, workgroup >::iterator it;
            it = mapwork.find(qid);
            if(it!=mapwork.end())
            {
                it.value().conditionlist.append(cd);;
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
