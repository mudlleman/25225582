#include "readpath.h"

ReadPath::ReadPath(QObject *parent) :
    QObject(parent)
{
    openFile();

    QMap<int, Pointpath>::iterator it;

    QList<PointRuntype> lsrunright;
    QList<PointRuntype> lsrunleft;
    m_preid=0;

    GetPath(9,7,6);
    //int dd=0;
}
void ReadPath::openFile()
{
    QString fileName="xml/path.xml";
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QDomDocument dom("WCM");
        if (dom.setContent(&file))
        {

            QDomElement docElem = dom.documentElement();
            GetPath(docElem);
        }
    }
    file.close();
}
void ReadPath::GetPath(QDomElement &docElem)
{

    QDomNode node = docElem.firstChild();
    while(!node.isNull())
    {
        QDomElement element = node.toElement(); // try to convert the node to an element.

        if( element.tagName()=="pointinfo" )
        {
            // <condtion id="1" type="gpio" CP="=" name="test" cpvalue="" address="" />

            PointPathStruct pp;
            if( element.hasAttribute("id") )
                pp.pathid= element.attributeNode("id").value().toInt();  
            m_pathmap.insert(pp.pathid,pp);
        }
        if( element.tagName()=="pointdirect" )
        {
            // <condtion id="1" type="gpio" CP="=" name="test" cpvalue="" address="" />
            Pointpath cd;
            if( element.hasAttribute("preid") )
                cd.preid= element.attributeNode("preid").value().toInt();
            if( element.hasAttribute("leftid") )
                cd.leftid= element.attributeNode("leftid").value().toInt();
            if( element.hasAttribute("rightid") )
                cd.rightid= element.attributeNode("rightid").value().toInt();
            if( docElem.hasAttribute("id") )
            {
                int idd= docElem.attributeNode("id").value().toInt();
                QMap<int, PointPathStruct>::iterator it;
                it = m_pathmap.find(idd);

                if(it!=m_pathmap.end())
                {
                    it.value().pathmap.insert(cd.preid,cd);
                }
            }
        }
        if( !element.isNull() )
        {
            GetPath(element);
        }
        node = node.nextSibling();
    }
    return;
}
bool ReadPath::justhavedigui(int pathid)
{
    QMap<int, int>::iterator it;
    it = m_HaveDigui.find(pathid);
    if(it==m_HaveDigui.end())
    {
        m_HaveDigui.insert(pathid,pathid);
        return true;
    }
    else
    {
        return false;
    }
}

QList<PointRuntype>  ReadPath::GetPath(int preid,int curid,int toid)
{
    m_preid=preid;
    QList<PointRuntype> rlist;

    QList<PointRuntype> lsrunright;
    QList<PointRuntype> lsrunleft;
    m_pathlist.clear();
    m_HaveDigui.clear();
    QMap<int, PointPathStruct>::iterator it;
    it = m_pathmap.find(curid);
    if(it != m_pathmap.end())
    {
        getpath(preid,it.value(),toid,lsrunright,lsrunleft);
    }
    if(m_pathlist.size()>0)
    {
        int tempint=0;
        for(int i=0;i<m_pathlist.size();i++)
        {
            pathliststruct tempstruct=m_pathlist[i];
            if(tempstruct.qlsit.size()>tempint)
            {
                tempint=tempstruct.qlsit.size();
                rlist=tempstruct.qlsit;
            }
        }
    }
    return rlist;
}

PointRuntype ReadPath::getretruntype(bool direct, int pathid, int toid)
{
    PointRuntype prtype;
    prtype.isright=direct;
    prtype.pathid=pathid;
    prtype.topathid=toid;
    return  prtype;
}

void ReadPath::insertinfindpath(int tagid,int passid, QList<PointRuntype> lsrun)
{
    if(tagid==passid)
    {
        if(!justinsertpath(m_preid,lsrun))
        {
            return;
        }

        pathliststruct pst;
        for (int i = 0; i < lsrun.size(); i++)
        {
            pst.qlsit.append(lsrun[i]);
        }
        m_pathlist.append(pst);
    }

}
bool ReadPath::justinsertpath(int preid,QList<PointRuntype> prt)
{
    bool br=true;
    if(prt.size()>0)
    {
        if(preid==prt[0].topathid||preid==0)
        {
            br=false;
        }
        /*
        for(int i=0;i<prt.size()-1;i++)
        {
            QMap<int, Pointpath>::iterator it;
            it = m_pathmap.find(prt[i].pathid);
            if( it != m_pathmap.end())
            {
               Pointpath  pp=it.value();
               if(pp.leftid==prt[i+1].topathid||pp.rightid==prt[i+1].topathid)
               {
                  br= false;
               }
            }
        }
        */
    }
    return br;


}

void ReadPath::getpath(int preid, PointPathStruct ppst, int tagid, QList<PointRuntype> lsrunright, QList<PointRuntype> lsrunleft)
{
    if(!justhavedigui(ppst.pathid))
    {
        return;
    }
    QMap<int, Pointpath>::iterator itp;
    itp =ppst.pathmap.find(preid);
    Pointpath pp;
    if(itp==ppst.pathmap.end())
    {
        return;
    }
    else
    {
        pp=itp.value();
    }
    QMap<int, PointPathStruct>::iterator it;
    it = m_pathmap.find(pp.leftid);
    if( it != m_pathmap.end())
    {
        PointPathStruct p = it.value();

        PointRuntype prtype=getretruntype(false,ppst.pathid,pp.leftid);
        lsrunleft.append(prtype);
        insertinfindpath(tagid,pp.leftid,lsrunleft);
        getpath(ppst.pathid, p, tagid, lsrunleft, lsrunleft);
    }
    else
    {
        PointRuntype prtype=getretruntype(false,ppst.pathid,pp.leftid);
        lsrunleft.append(prtype);
        insertinfindpath(tagid,pp.leftid,lsrunleft);
    }
    it = m_pathmap.find(pp.rightid);
    if( it != m_pathmap.end())
    {
        PointPathStruct p = it.value();
        PointRuntype prtype=getretruntype(true, ppst.pathid, pp.rightid);
        lsrunright.append(prtype);
        insertinfindpath(tagid,pp.rightid,lsrunright);
        getpath(ppst.pathid,p, tagid, lsrunright, lsrunright);
    }
    else
    {
        PointRuntype prtype=getretruntype(true, ppst.pathid, pp.rightid);
        lsrunright.append(prtype);
        insertinfindpath(tagid,pp.rightid,lsrunright);

    }

}
