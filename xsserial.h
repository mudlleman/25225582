#ifndef XSSERIAL_H_
#define XSSERIAL_H_
#include <QString>
#include <QObject>
class QTimer;
struct serial_config
{
    const  char *serial_dev;
    unsigned int serial_speed;
    unsigned char databits;
    unsigned char stopbits;
    unsigned char parity;
};

class xsserial: public QObject
{
    Q_OBJECT
public:
    xsserial(QObject *parent);
    ~xsserial();

public:
    bool Open(QString portName,int baudRate);
    void serial_close();
    int serial_read();
    bool serial_write(char * buff2,int dataLength);
private:
      //Posix_QextSerialPort *m_posixCom;
    void serial_init();



    void set_speed(int fd);
    int set_Parity(int fd);
    int OpenDev(char *Dev);



private:

    serial_config serialdata;

    int serial_fd;

    char open_flag;

public:

    char uart_buff[512];

};

#endif /*XSSERIAL_H_*/
