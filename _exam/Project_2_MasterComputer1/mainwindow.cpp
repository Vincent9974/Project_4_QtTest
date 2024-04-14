#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::monitor()
{
    //串口初始化
    serialPort = new QSerialPort;

    //设置使用哪个串口
    serialPort->setPortName("COM2");
    //打开串口
    if(!serialPort->open(QIODevice::ReadWrite))
    {
        QMessageBox::critical(nullptr,
                              "串口打开失败",
                              "串口COM2不存在或者已被占用!",
                              QMessageBox::Ok);
        QTimer::singleShot(0, qApp, SLOT(quit()));
    }

    serialPort->setBaudRate(19200);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    senderThread = new SendPack(serialPort);
    senderThread->start();

}
