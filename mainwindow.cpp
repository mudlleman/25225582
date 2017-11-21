#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //qDebug()>>"121212";
   // qDebug()<<"121212";
}

MainWindow::~MainWindow()
{
    delete ui;
}
