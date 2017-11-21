#include "ludp.h"
#include <QDebug>
#include   <stdio.h>
#include   <sys/ioctl.h>
#include   <sys/socket.h>
#include   <netinet/in.h>
#include   <net/if.h>
#include   <string.h>
ludp::ludp(QObject *parent) :
    QThread(parent)
{
   // start();
   // getlocalip();
    //  sendata();
    //recivedata();
}
void ludp::sendata(QByteArray qb)
{

    QHostAddress  Ip_Tx = QHostAddress("192.168.0.255");
    QUdpSocket *sender;
    sender = new QUdpSocket(this);
    sender->writeDatagram(qb.data(),qb.size(),Ip_Tx,6000);
    delete sender;

}
bool ludp::justlocalid(QString ip)
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

void ludp::getlocalip()
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


void ludp::recivedata()
{
    qDebug()<<11111;
    emit udprecstr("nn");
}

void ludp::run()
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
                sprintf(rsmsg,"%s:%s\t",ip, smsg);

                QString nn = QString(QLatin1String(rsmsg));
                recivedata();
                nn =nn.simplified();

                qDebug()<<nn;
            }
        }

        // sleep(1);
    }

    //   return 0;
}
void ludp::getMac()
{
      ifreq   ifreq;
       int   sock;


       if((sock=socket(AF_INET,SOCK_STREAM,0)) <0)
       {
           perror( "socket ");
           return   ;
       }
       strcpy(ifreq.ifr_name,"eth1");
       if(ioctl(sock,SIOCGIFHWADDR,&ifreq) <0)
       {
           perror( "ioctl ");
           return   ;
       }
       printf( "%02x:%02x:%02x:%02x:%02x:%02x\n ",
               (unsigned   char)ifreq.ifr_hwaddr.sa_data[0],
               (unsigned   char)ifreq.ifr_hwaddr.sa_data[1],
               (unsigned   char)ifreq.ifr_hwaddr.sa_data[2],
               (unsigned   char)ifreq.ifr_hwaddr.sa_data[3],
               (unsigned   char)ifreq.ifr_hwaddr.sa_data[4],
               (unsigned   char)ifreq.ifr_hwaddr.sa_data[5]);
       return   ;
}
