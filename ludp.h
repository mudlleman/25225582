#ifndef LUDP_H
#define LUDP_H
#include <QtNetwork>
#include <QThread>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <malloc.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include <fcntl.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "owntimer.h"
class ludp : public QThread
{
    Q_OBJECT
public:
    explicit ludp(QObject *parent = 0);
    void sendata(QByteArray qb);
    void recivedata();
    void run();
private:
    void getMac();
    void getlocalip();
    bool justlocalid(QString ip);
    QList<QString> m_listip;
     OWNTimer m_threadTime;


public :
signals:
    void udprecstr(QString recstr);
    void testsing(int n);
public slots:
    
};

#endif // LUDP_H
