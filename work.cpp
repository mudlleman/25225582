#include "work.h"

work::work(QObject *parent) :
    QThread(parent)
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
void work::setinterface(control *ct, condition *cd)
{
    m_control=ct;
    m_conditon=cd;
}
void work::run()
{
    QString workid=m_workid;
    qDebug()<<workid;
    QMap<QString, workgroup>::iterator it;

    it = mapwork.find(workid);

    if(it!=mapwork.end())
    {
        qDebug()<< "mapwork"<<mapwork.size();
        QList<workstep> sds= it.value().conditionlist;
        for(int i=0;i<sds.size();i++)
        {
            workstep wkstep=sds[i];
            QStringList cons= wkstep.condtiongroup.split(",");
            QStringList cts=wkstep.controlgroup.split(",");
            bool btrue=true;
            for(int i=0;i<cons.size();i++)
            {

                int cdid=cons.at(i).toInt();

                bool tempb= m_conditon->GetMapConndtion(cdid);
                qDebug()<<"aaabbbccc"<<cdid<<tempb;
                if(tempb)
                {
                    int ctlid=cts.at(i).toInt();
                    qDebug()<<"aaabbbccceee"<<ctlid;
                    m_control->execute(ctlid);
                }
            }
        }
    }
}

void work::executework(QString workid)
{
    m_workid=workid;
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
