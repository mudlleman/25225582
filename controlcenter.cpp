#include "controlcenter.h"
#include "QDebug"
ControlCenter::ControlCenter(QObject *parent) :
    QThread(parent)
{ 




    CanNetControl=false;
    m_bgetsetplong=false;
    DirveSystemNumber=1;
    m_getnv=new NavManger(DirveSystemNumber);
    netidsteplen=0;
    CompareValue=300;
    originalID=100;
    willarriveid=0;
    NetSpeedbl=1;
    m_runlist.append(7);
    m_runlist.append(1);
    m_runlist.append(9);
    //m_runlist.append(15);
    curpathid=0;
    prearrid=0;
    arriveid=7;
    m_bstop=false;
    NetControlGpioNumber=0;


    m_madacontrol1=new MadaControl("/dev/ttySP2");
    m_madacontrol2=new MadaControl("/dev/ttySP3");

    connect(&m_threadTime ,SIGNAL(TimeoutEvent()),this,SLOT(GetReadValue()));
    connect(&m_getpathpid, SIGNAL(readidsingal(int)), this, SLOT(pathid(int)));

    kp = 0.0048f;
    ki = 0.00000f;
    kd = 0.0025f;
    m_threadTime.startrun(70);

    m_netspeed=0;
    init();
    m_setspeed=500;
    getlocalip();
    start();
    //m_speedpulse.start();

}
int tempspeed=0;
int runnumber=0;
int netcontorlnubmer=0;
void  ControlCenter::GetReadValue()
{

    runnumber++;

    StopType stype=gorun;

    //检测时候打开
  //  StopType stype=GetSate();

    if(CanNetControl)
    {
        tempspeed=m_netspeed;
        stype=gorun;
        netcontorlnubmer++;
    }
   // qDebug()<<netcontorlnubmer;
    if(netcontorlnubmer>20)
    {
        tempspeed=0;
    }
    if(runnumber%10==0)
    {
        SendCurInfobyUdp();

    }
    if(runnumber%5==0&&stype==gorun&&!CanNetControl)
    {
        if(tempspeed<m_setspeed)
        {
            tempspeed+=100;
        }
        else
        {
            tempspeed=m_setspeed;
        }
    }

    if(stype==NowStop)
    {
        tempspeed=0;

    }
    if(stype==FreeStop)
    {
        if(tempspeed>0)
        {
            tempspeed=tempspeed-100;
        }
        if(tempspeed<0)
        {
            tempspeed=0;
        }
    }

    SetMdSpeed(tempspeed,1);

    if(CanNetControl)
    {
        return;
    }

    if(tempspeed==0)
    {
        ExcueAfterArrive();
    }
    CalPath();

    ExcuePassid();



}
int excutemp=0;
void ControlCenter::ExcueAfterArrive()
{
    if(arriveid==curpathid)
    {
        if(arriveid!=excutemp)
        {
            qDebug()<<"arrive!";
            m_threadTime.mmsleep(30);
            SetMdSpeed(0,0);
            excutemp=arriveid;
            QString keys=QString::number(arriveid, 10)+"end";
            m_work.executework(keys);
            m_work.run();
            m_work.wait();
            SetNextArrive(arriveid);
            qDebug()<<"arriveid"<<arriveid;
        }
    }
}
int passtempid=0;
void ControlCenter::ExcuePassid()
{
    if(arriveid!=curpathid)
    {
        if(curpathid!=0&&passtempid!=curpathid)
        {
            qDebug()<<3333333;
            passtempid=curpathid;
            QString keys=QString::number(curpathid, 10)+"pass";


            m_work.executework(keys);
            m_work.run();
            m_work.wait();
            // m_speedpulse.initvalue(0);
            //m_madacontrol1->setcurpostion( m_madacontrol1->getpostion());
            SetNavType(curpathid);
        }
    }
}
void ControlCenter::GetSetplongSend()
{
    if(m_bgetsetplong&&m_listpassid.size()>2)
    {
        QString steplong=QString::number(m_madacontrol1->getpostion(),10);

        QString pre=QString::number(m_listpassid.at(0),10);
        QString cur=QString::number(m_listpassid.at(1),10);
        QString arr=QString::number(m_listpassid.at(2),10);

        QString sendstr="pathset "+ pre+" "+cur+" "+arr+" "+steplong;

        QByteArray cstr = sendstr.toAscii();
        tcpSocket->write(cstr);
        m_ludp.sendata(cstr);
    }


}
float ControlCenter::LowSpeed()
{
    // netidsteplen
    if(willarriveid==arriveid)
    {
        int haverunstep=m_madacontrol1->getpostion();
        float willstep= netidsteplen-haverunstep;
        if(willstep>0&&CompareValue<willstep)
        {
            float bl=willstep/CompareValue;
            if(bl>1)
            {
                bl=1;
            }
            return bl;
        }
    }
    return 1;
}

void ControlCenter::SetNavType(int pathid)
{
    //if(m_qlistpasspath.siz)
    for(int i=0;i<m_qlistpasspath.size();i++)
    {
        PointRuntype pr=m_qlistpasspath[i];
        if(pr.pathid==pathid)
        {
            m_getnv->SetCanTurn(pr.isright);
            netidsteplen=pr.steplen;
            willarriveid =pr.topathid;
            break;
        }
    }

}

float ControlCenter::GetCalMdSpeed(bool direct, float speed, float bl)
{
    float calspeed=speed;
    //判断是否是内侧马达
    if(direct)
    {
        if(bl>0)
        {
            calspeed=speed-speed*bl*2;
        }
    }
    else
    {
        if(bl<0)
        {
            calspeed=speed+speed*bl*2;
            calspeed=0-calspeed;
        }
    }
}

void ControlCenter::SetMdSpeed(float speed)
{

    QByteArray Qtarry[4];
    float  m_nv=m_getnv->GetNavigationValue(0);
    float bl=m_pid.GetPidFloat(kp,ki,kd,m_nv);

    float speed1=GetCalMdSpeed(true,speed,bl);
    float speed2=GetCalMdSpeed(false,speed,bl);

     Qtarry[1]= controlbyte.GetSpeedByte(1,speed1);

      Qtarry[2]= controlbyte.GetSpeedByte(1,speed2);


    if(DirveSystemNumber==2)
    {
         m_nv=m_getnv->GetNavigationValue(1);
         bl=m_pid.GetPidFloat(kp,ki,kd,m_nv);

         speed1=GetCalMdSpeed(true,speed,bl);
         speed2=GetCalMdSpeed(false,speed,bl);

         Qtarry[3]= controlbyte.GetSpeedByte(1,speed1);

         Qtarry[4]= controlbyte.GetSpeedByte(1,speed2);
    }

    m_madacontrol1->wirtedata(qtsend1);

    m_madacontrol2->wirtedata(qtsend2);


}

void ControlCenter::CalPath()
{
    //路径的节点要小于10000
    if(curpathid>10000)
    {
        return;
    }
    if(prearrid!=curpathid)
    {
        if(curpathid!=0&&prearrid!=0)
        {
            netidsteplen=0;

            m_qlistpasspath.clear();
            m_qlistpasspath=m_readpath.GetPath(prearrid,curpathid,arriveid);

            for(int i=0;i<m_qlistpasspath.size();i++)
            {
                PointRuntype prtype=m_qlistpasspath[i];
                qDebug()<<"id"<<prtype.pathid<<"right"<<prtype.isright<<prtype.topathid;
            }
        }
        if(m_bgetsetplong)
        {
            m_bgetsetplong=false;
            GetSetplongSend();
            m_bstop=true;
        }
        //m_speedpulse.initvalue(0);
        m_madacontrol1->setcurpostion(m_madacontrol1->getpostion());
        prearrid=curpathid;
    }
}

void ControlCenter::pathid(int id)
{
    if(id==0)
    {
        return;
    }
    curpathid=id;

    if(curpathid<10000)
    {
        for(int i=0;i<m_listpassid.size();i++)
        {
            int tempint=m_listpassid.at(i);
            if(tempint==curpathid)
            {
                return ;
            }
        }
        qDebug()<<"vvv"<<curpathid ;
        m_listpassid.append(curpathid);
        if(m_listpassid.size()>3)
        {
            m_listpassid.pop_back();
        }
    }

}
void ControlCenter::SetNextArrive(int curid)
{
    int index=-1;
    for(int i=0;i<m_runlist.size();i++)
    {
        if(m_runlist[i]==curid)
        {
            index=i;
            break;
        }
    }
    if(index>-1&index<(m_runlist.size()-1))
    {
        arriveid=m_runlist[index+1];
    }
    if(index==(m_runlist.size()-1))
    {
        arriveid=m_runlist[0];
    }
}
bool temparrive=true;
StopType ControlCenter::GetSate()
{
    StopType stopType=gorun;
    bool br=true;

    if(!m_gpio.GetCheckGpio())
    {
        stopType=NowStop;

        br=false;
    }
    if(curpathid==arriveid&&curpathid!=0)
    {
        stopType=FreeStop;
        br=false;
    }
    if(m_bstop)
    {
        stopType=NowStop;
        br=false;
    }
    return stopType;
}

void ControlCenter::SendCurInfobyUdp()
{
    int nvnv=-1000;
    QString nvstr=QString::number(nvnv,10);
   // m_batv=m_gpio.GetAdc();
    QString steplong=QString::number(m_madacontrol1->getpostion(),10);

    QString pre=QString::number(prearrid,10);
    QString arr=QString::number(curpathid,10);
    QString wil=QString::number(willarriveid,10);
    QString ari=QString::number(arriveid,10);
    QString qbat=QString::number(m_batv,'g',6);

    QString stata=" stat ";
    StopType stype=GetSate();
    if(stype==gorun)
    {
        stata=stata+":run";
    }
    else
    {
        stata=stata+":stop";
    }

    QString sendstr="cruinfo pre:"+ pre+" cru:"+arr+" wil:"+wil+" ari: "+ari +" run:"+steplong+" nv:"+nvstr+" bat:"+qbat+stata;

    QByteArray cstr = sendstr.toAscii();
    m_ludp.sendata(cstr);
   // qDebug()<<sendstr;
}


void ControlCenter::init()
{

    m_cotrol.SetControlface(&m_setspeed,&m_gpio,m_madacontrol1,m_madacontrol2);
    m_condition.SetControlface(&m_setspeed,&m_gpio,m_madacontrol1,m_madacontrol2);
    m_work.setinterface(&m_cotrol,&m_condition);
/*
    m_work.executework("7end");
    m_work.run();
    m_work.wait();
*/
    //  qDebug()<<"setspeed"<<m_setspeed;
    this->tcpSocket = new QTcpSocket(this);

    newTCPConnect();

    //这里我是采用程序启动就自访问服务端（也可根据实际情况采用手动连接手动输入服务端ip的方式。）

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(revData()));

    //readyRead()表示服务端发送数据过来即发动信号，接着revData()


    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),

            this,SLOT(displayError(QAbstractSocket::SocketError)));

}

void ControlCenter::ludpvalue(QString qstr)
{
 //   qDebug()<<"control:"<<qstr;
    QStringList qsl= qstr.split(' ');
  //  qDebug()<<qsl.at(0)<<"--"<<qsl.at(1);
    if(qsl.size()>1)
    {
        if(qsl.at(0)=="gotoid")
        {
            if(curpathid==originalID)
            {
                arriveid=qsl.at(1).toInt();
            }
        }

        if(qsl.at(0)=="mdstep")
        {
            int mad1step=qsl.at(1).toInt();
            int mad2step=qsl.at(2).toInt();
            m_madacontrol1->controlstep(mad1step);
            m_madacontrol2->controlstep(mad2step);

        }
        if(qsl.at(0)=="setlong"&&qsl.length()==3)
        {
            bool setdirect=false;
            if(qsl.at(1)=="true")
            {
                setdirect=true;
            }
            m_getnv->SetCanTurn(setdirect);
            arriveid=qsl.at(2).toInt();
            m_runlist.clear();
            m_setspeed=1000;
            m_bstop=false;
            m_bgetsetplong=true;
            qDebug()<<"setlong";
        }
        //能够从事网络控制
        // qDebug()<<qsl[0]<<"vvvvvv";
       if(qsl.at(0)=="netcl")
       {
          // qDebug()<<qsl[1]<<"vvvvvv";
           if(qsl.at(1)=="true")
           {
               CanNetControl=true;
               m_setspeed=0;
               NetSpeedbl=0;
               NetSpeedbl=0;
               m_netspeed=0;


           }
           else
           {
               CanNetControl=false;
                m_setspeed=0;
                NetSpeedbl=0;
                m_netspeed=0;
           }
       }
        if(qsl.at(0)=="netspeedbl")
        {
            NetSpeedbl=qsl.at(1).toInt();
            m_netspeed=qsl.at(2).toInt();
            int tempgpio=qsl.at(3).toInt();
            netcontorlnubmer=0;
            if(NetControlGpioNumber!=tempgpio)
            {
                NetControlGpioNumber=tempgpio;
                if(NetControlGpioNumber==122)
                {
                    SetGpio(117,true);
                }
               if(NetControlGpioNumber==123)
                {
                     SetGpio(117,false);
                }

                qDebug()<<"gpio"<<NetControlGpioNumber;
            }
           // qDebug()<<m_netspeed<<"setttttt"<<qsl.at(2);
        }

        if(qsl.at(0)=="speed"&&qsl.length()==2)
        {
            m_setspeed=qsl.at(1).toInt();
            qDebug()<<"speedaaaa    ";
        }

        //  qDebug()<<qsl;
    }
}
void ControlCenter::SetGpio(int nubmer,bool SetValue)
{


     QString setadress="/sys/class/gpio/gpio"+QString::number(nubmer,10)+"/value";
      m_gpio.SetGpio(setadress,SetValue);
}

void ControlCenter::revData()

{

    QString datas = tcpSocket->readAll();

    QStringList qsl= datas.split(' ');

    if(qsl.at(0)=="setlong"&&qsl.length()==3)
    {
        bool setdirect=false;
        if(qsl.at(1)=="true")
        {
            setdirect=true;
        }
        m_getnv->SetCanTurn(setdirect);
        arriveid=qsl.at(2).toInt();
        m_runlist.clear();
        m_setspeed=1000;

        m_bstop=false;
        m_bgetsetplong=true;
        qDebug()<<"setlong";
    }
    if(qsl.at(0)=="pid"&&qsl.length()==4)
    {
        kp =qsl.at(1).toFloat();
        ki =qsl.at(2).toFloat();
        kd =qsl.at(3).toFloat();
        QString qs=qsl.at(3);
        qDebug()<<qsl;
        qDebug()<<"pid"<<kp<<ki<<kd;

    }

    if(qsl.at(0)=="speed"&&qsl.length()==2)
    {
        m_setspeed=qsl.at(1).toInt();
        qDebug()<<"speedaaaa    ";
    }



}



void ControlCenter::newTCPConnect()

{

    tcpSocket->abort();

    tcpSocket->connectToHost("192.168.43.130",6666);

    //这里可以根据实际情况在用户界面上进行输入。

}
void ControlCenter::displayError(QAbstractSocket::SocketError)

{

    qDebug()<<tcpSocket->errorString();

    tcpSocket->close();

}


bool ControlCenter::justlocalid(QString ip)
{
    for(int i=0;i<m_listip.size();i++)
    {
        QString str=m_listip.at(i);
        if(str==ip)
        {
            return true;
        }
    }
    return false;
}

void ControlCenter::getlocalip()
{
    QNetworkInterface * test = new QNetworkInterface();
    qDebug() << test->allAddresses();
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            qDebug()<<address.toString();
        m_listip.append(address.toString());
    }
}



void ControlCenter::run()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    fflush(stdout);

    // 绑定地址
    struct sockaddr_in addrto;
    bzero(&addrto, sizeof(struct sockaddr_in));
    addrto.sin_family = AF_INET;
    addrto.sin_addr.s_addr = htonl(INADDR_ANY);
    addrto.sin_port = htons(6000);

    // 广播地址
    struct sockaddr_in from;
    bzero(&from, sizeof(struct sockaddr_in));
    from.sin_family = AF_INET;
    from.sin_addr.s_addr = htonl(INADDR_ANY);
    from.sin_port = htons(6000);

    int sock = -1;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        //cout<<"socket error"<<endl;
        return ;
    }

    const int opt = 1;
    //设置该套接字为广播类型，
    int nb = 0;
    nb = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
    if(nb == -1)
    {
        //cout<<"set socket error..."<<endl;
        return ;
    }

    if(bind(sock,(struct sockaddr *)&(addrto), sizeof(struct sockaddr_in)) == -1)
    {
        //cout<<"bind error..."<<endl;
        return ;
    }

    int len = sizeof(sockaddr_in);


    while(1)
    {
        //从广播地址接受消息
         char smsg[100] = {0};
        int ret=recvfrom(sock, smsg, 100, 0, (struct sockaddr*)&from,(socklen_t*)&len);
        if(ret<=0)
        {
            //cout<<"read error...."<<sock<<endl;
        }
        else
        {

            char *ip =inet_ntoa(from.sin_addr);
          //  printf("%s\n",inet_ntoa(from.sin_addr));

            QString fromip=QString(QLatin1String(ip));
            if(!justlocalid(fromip))
            {
                char rsmsg[100] = {0};
                sprintf(rsmsg,"%s\t", smsg);

                QString nn = QString(QLatin1String(rsmsg));

                nn =nn.simplified();
                ludpvalue(nn);
               // qDebug()<<nn;
            }
        }

        // sleep(1);
    }

    //   return 0;
}
