#ifndef CONTROLCENTER_H
#define CONTROLCENTER_H

#include <QObject>
#include<QtNetwork>

#include<QtNetwork/QTcpSocket>

#include"navmanger.h"
#include "pidcalculate.h"
#include "xsserial.h"
#include "ccontrolbyte.h"
#include "condition.h"
#include "pathrfid.h"
#include "madacontrol.h"
#include "work.h"
#include "readpath.h"
#include"speedpulse.h"
#include "ludp.h"

enum StopType{NowStop,FreeStop,gorun};
//enum  Direectenum { front, back, left,right};
class ControlCenter : public QThread
{
    Q_OBJECT
public:
    explicit ControlCenter(QObject *parent = 0);
       void run();
private:
    //  Direectenum m_Direect;

    void getlocalip();
    bool justlocalid(QString ip);
    QList<QString> m_listip;

//pid 调节参数
    float kp ;
    float ki ;
    float kd ;
    //当前电池运行电量
    double m_batv;

    //原始等待点
    int originalID;
    //当前经过点
    int curpathid;
    //到达的点
    int arriveid;
    //上个节点
    int prearrid;
    //区间距离
    int netidsteplen;
    //将要到达的点
    int willarriveid;

    //是否进行网络控制
    bool CanNetControl;

    //网络控制的差速比
    float NetSpeedbl;
    //通过网络控制GPIO
    int NetControlGpioNumber;

    int CompareValue;

    //驱动单元数量
    int DirveSystemNumber;


    //SpeedPulse m_speedpulse  ;

    ReadPath m_readpath;

    QList<PointRuntype> m_qlistpasspath;
    QList<int> m_runlist;

    QVector<int> m_listpassid;
    NavManger *m_getnv;
    OWNTimer m_threadTime;
    PidCalculate m_pid;
    float m_setspeed;
    float m_netspeed;
    CcontrolByte controlbyte;
    QTcpSocket *tcpSocket;
    PathRfid m_getpathpid;


    MadaControl *m_madacontrol1;
    MadaControl *m_madacontrol2;
    Gpio m_gpio;
    work m_work;
    condition m_condition;
    control m_cotrol;
    ludp m_ludp;

    bool m_bgetsetplong;
    bool m_bstop;




    //获取当前的运行状态
    StopType GetSate();

    float GetCalMdSpeed(bool direct,float speed,float bl);
    // 设置马达速度
    void SetMdSpeed(float speed);
    //就算路径
    void CalPath();
    //到达后执行
    void ExcueAfterArrive();
    //经过执行
    void ExcuePassid();
    //设置是否转向
    void SetNavType(int pathid) ;
    //设置下个目标
    void SetNextArrive(int curid);

    //发送当前信息
    void SendCurInfobyUdp();

    //获取当前运行的距离
    void GetSetplongSend();

    //通过数字量控制Gpio
    void SetGpio(int nubmer,bool SetValue);


    float LowSpeed();


    void init();
    void newTCPConnect();//用于建立服务端与客户之间的连接函数

public:
    
signals:
    
public slots:
    void GetReadValue();
    void pathid(int id);
    void ludpvalue(QString qstr);





    void revData(); //接收来自服务端的数据
    void displayError(QAbstractSocket::SocketError);
};

#endif // CONTROLCENTER_H
