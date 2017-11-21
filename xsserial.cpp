#define linuxcom 1
#include "xsserial.h"

#define DATA_LEN                0x08
#if linuxcom
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <termios.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include"pthread.h"
#endif

#include <QThread>
#include <QTimer>
#include <QVector>
#include <QDebug>

#define FALSE		0
#define TRUE		1

xsserial::xsserial(QObject *parent)
 : QObject(parent)
{

}

xsserial::~xsserial()
{
}

bool xsserial::Open(QString portName,int baudRate)
{


#if linuxcom
    int m_index=-1;
   unsigned int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1200, B300,B38400, B19200, B9600, B4800, B2400, B1200, B300, };

    int name_arr[] = {38400,  19200,  9600,  4800,  2400,  1200,  300, 38400, 19200,  9600, 4800, 2400, 1200,  300, };
    for(int i=0;i<14;i++)
    {
        if(name_arr[i]==baudRate)
        {
            m_index=i;
            break;
        }
    }


   // portName = "/dev/" + portName;   //获取串口名

    serialdata.serial_dev = portName.toAscii();

    serialdata.serial_speed=16;
    serialdata.databits = 8;
    serialdata.stopbits = 1;
    serialdata.parity = 'N';

    serial_init();

    open_flag=1;

#endif
     return true;
}

void xsserial::set_speed(int fd)
{
    #if linuxcom
    unsigned int i;
    int status;
    struct termios Opt;
    struct termios oldOpt;
    tcgetattr(fd, &oldOpt);
    tcflush(fd, TCIOFLUSH);
    cfsetispeed(&Opt, serialdata.serial_speed);
    cfsetospeed(&Opt, serialdata.serial_speed);

   // qDebug()<<"mmmmmmasfadsaf"<< serialdata.serial_speed;
    status = tcsetattr(fd, TCSANOW, &Opt);
    if(status != 0)
    {
        perror("tcsetattr fd1");
        return;
     }
     tcflush(fd, TCIOFLUSH);

    #endif
}


//-----------------------------------------------
//设置其他参数
int xsserial::set_Parity(int fd)
{
    #if linuxcom
        struct termios options;
        struct termios oldoptions;
        if(tcgetattr(fd, &oldoptions) != 0)
        {
                perror("SetupSerial 1");
                return(FALSE);
        }
        bzero(&options,sizeof(options));
        options.c_cflag |= (CLOCAL|CREAD);
        options.c_cflag &=~CSIZE;
        switch(serialdata.databits)
        {
                case 7:
                        options.c_cflag |= CS7;
                        break;
                case 8:
                        options.c_cflag |= CS8;
                        break;
                default:
                        options.c_cflag |= CS8;
                        fprintf(stderr, "Unsupported data size\n");
                        return(FALSE);
        }

        switch(serialdata.parity)
        {
                case 'n':
                case 'N':
                        options.c_cflag &= ~PARENB;
                        options.c_iflag &= ~INPCK;
                        break;
                case 'o':
                case 'O':
                        options.c_cflag |= (PARODD | PARENB);
                        options.c_iflag |= INPCK;
                        break;
                case 'e':
                case 'E':
                        options.c_cflag |= PARENB;
                        options.c_cflag &= ~PARODD;
                        options.c_iflag |= INPCK;
                        break;
                default:
                        options.c_cflag &= ~PARENB;
                        options.c_iflag &= ~INPCK;
                        fprintf(stderr, "Unsupported parity\n");
                        return(FALSE);
        }

        switch(serialdata.stopbits)
        {
                case 1:
                        options.c_cflag &= ~CSTOPB;
                        break;
                case 2:
                        options.c_cflag |= CSTOPB;
                        break;
                default:
                        options.c_cflag &= ~CSTOPB;
                        fprintf(stderr, "Unsupported stop bits\n");
                        return(FALSE);
        }
        if(serialdata.parity != 'n')
                options.c_iflag |= INPCK;
        options.c_cc[VTIME] = 0;	//150;			//15 seconds
        options.c_cc[VMIN] = 0;

        options.c_iflag |= IGNPAR|ICRNL;
        options.c_oflag |= OPOST;
        options.c_iflag &= ~(IXON|IXOFF|IXANY|IUCLC);

        options.c_oflag = ~OPOST;


        tcflush(fd, TCIFLUSH);
        if(tcsetattr(fd, TCSANOW, &options) != 0)
        {
                perror("SetupSerial 3");
                return(FALSE);
        }
#endif
        return(TRUE);
}

int xsserial::OpenDev(char *Dev)
{
    int fd =-1;
     #if linuxcom
         fd = open(Dev, O_RDWR, 0);
        if(-1 == fd)
        {
                perror("Can't Open Serial Port%s");
                return -1;
        }
#endif
        return fd;
}

//--------------------------------------------------
//串口初始化
//--------------------------------------------------
void xsserial::serial_init(void)
{
    #if linuxcom
        char *Dev;


        Dev = (char * )serialdata.serial_dev;
        //打开串口设备
         serial_fd = OpenDev(Dev);

        if(serial_fd > 0)
                set_speed(serial_fd);		//设置波特率
        else
        {
                printf("Can't Open Serial Port!\n");
                exit(0);
        }
        //恢复串口未阻塞状态
        if (fcntl(serial_fd, F_SETFL, O_NONBLOCK) < 0)
        {
                printf("fcntl failed!\n");
                exit(0);
        }

        if(set_Parity(serial_fd) == FALSE)
        {
                printf("Set parity Error\n");
                exit(1);
        }
#endif

}


void xsserial::serial_close(){
#if linuxcom
    int fd;

    fd = serial_fd;

    close(serial_fd);
#endif

}

bool xsserial::serial_write(char * buff2,int dataLength)
{
       #if linuxcom
    int dd=strlen(buff2);

     write(serial_fd,buff2,dataLength);
     #endif
        return true;

}
int xsserial::serial_read()
{
     //qDebug()<<"aaaasssssaaa";
 int nread=0;
   #if linuxcom
    // qDebug()<<"aaaasssssaaa"<<nread;
     nread = read(serial_fd,uart_buff,512);
     //qDebug()<<"aaaaaaa"<<nread;
    if(nread>0)
    {
        QVector< unsigned char> dataBuffer(nread);
        for(int j=0;j<nread;j++)
        {
            dataBuffer[j]=(unsigned char)uart_buff[j];
          //  fprintf(stderr,"%x ",dataBuffer[j]);

        }

     // qDebug()<<dataBuffer;
    }
     #endif
    return nread;
}

