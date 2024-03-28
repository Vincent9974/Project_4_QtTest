#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this,SIGNAL(ComeOn(QString& )),this,SLOT(ComeGuys(QString&)));
    connect(this,SIGNAL(ComeOn(QString& )),this,SLOT(ComeChina()));
    connect(this,SIGNAL(ComeOn(QString& )),this,SLOT(ComeHuaxia()));
    //connect(this,&MainWindow::ComeOn,this,&MainWindow::ComeGuys);

    connect(this,SIGNAL(ComeOn2()), this, SLOT(ComeHuaxia()));
    connect(this,SIGNAL(ComeOn3()), this, SLOT(ComeHuaxia()));
    connect(this,SIGNAL(ComeOn4()), this, SLOT(ComeHuaxia()));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_shButton_clicked()
{
    QString str = "上海";
    emit ComeOn(str);
}

void MainWindow::on_chButton_clicked()
{
    QString str = "中国";
    emit ComeOn(str);
}

void MainWindow::on_wdButton_clicked()
{
    QString str = "世界";
    emit ComeOn(str);
    emit ComeOn2();
    emit ComeOn3();
    emit ComeOn4();
}

void MainWindow::ComeGuys(QString &str)
{
    qDebug() << str;
}

void MainWindow::ComeChina()
{
    qDebug() << "China !!!";
}

void MainWindow::ComeHuaxia()
{
    qDebug() << "HuaXia !!!";
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() <<"断开ComeOn信号与ComeOnGuys的连接";
    disconnect(this,SIGNAL(ComeOn(QString&)),this,SLOT(ComeGuys(QString&)));
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug() <<"断开ComeOn信号与其响应的所有槽的连接";
    disconnect(this,SIGNAL(ComeOn(QString&)),0,0);
}

void MainWindow::on_pushButton_3_clicked()
{
    qDebug() <<"断开this所有信号与其响应的this所有槽的连接";
    disconnect(this,0,this,0);
}
