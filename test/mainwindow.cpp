#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}


void MainWindow::init()

{

   this->tcpSocket = new QTcpSocket(this);



   newTCPConnect();

       //这里我是采用程序启动就自访问服务端（也可根据实际情况采用手动连接手动输入服务端ip的方式。）

   connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(revData()));

     //readyRead()表示服务端发送数据过来即发动信号，接着revData()


   connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),

           this,SLOT(displayError(QAbstractSocket::SocketError)));

}



void MainWindow::revData()

{

   QString datas = tcpSocket->readAll();

   QStringList qsl= datas.split(' ');
    qDebug()<<qsl.length();
    float b=qsl.at(1).toFloat();
    qDebug()<<b;

   //this->ui->Ui_MainWindow.centralWidget->tabletEvent();
//接收字符串数据。

 //  ui->->setText(datas);
   //ui->centralWidget->
   //this->ui->Ui_Ma
   //this->ui->
    //this->ui->centralWidget->texs
     //显示字符串数据。
  //  ui->centralWidget->

}



void MainWindow::newTCPConnect()

{

   tcpSocket->abort();

   tcpSocket->connectToHost("192.168.169.100",6666);

      //这里可以根据实际情况在用户界面上进行输入。

}



void MainWindow::displayError(QAbstractSocket::SocketError)

{

   qDebug()<<tcpSocket->errorString();

   tcpSocket->close();

}





MainWindow::~MainWindow()
{
    delete ui;
    unsigned char willSend[20];
}


void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"asdfasdf";


}
