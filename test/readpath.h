#ifndef READPATH_H
#define READPATH_H

#include <QObject>
#include<QtXml>
#include<QMap>
struct Pointpath
{
    int preid;
    int leftid;
    int rightid;
};
struct PointPathStruct
{
    int pathid;
    QMap<int,Pointpath> pathmap;
};


struct PointRuntype
{
    int pathid;
    bool isright;
    int topathid;
};
struct pathliststruct
{
    QList<PointRuntype> qlsit;
};

class ReadPath : public QObject
{
    Q_OBJECT
public:
    explicit ReadPath(QObject *parent = 0);
    QList<PointRuntype>  GetPath(int preid, int curid,int toid);
private:
    QMap<int,PointPathStruct> m_pathmap;
    QMap<int ,int>m_HaveDigui;
    QList<pathliststruct> m_pathlist;
    int m_preid;

    void openFile();
    void GetPath(QDomElement& docElem);
    void getpath(int preid,PointPathStruct ppst, int tagid, QList<PointRuntype> lsrunright, QList<PointRuntype> lsrunleft);
    bool justinsertpath(int preid, QList<PointRuntype> prt);
    bool justhavedigui(int  pathid);



    PointRuntype getretruntype(bool direct, int pathid, int toid);
    void insertinfindpath(int tagid,int passid, QList<PointRuntype> lsrun);
    
signals:
    
public slots:
    
};

#endif // READPATH_H
