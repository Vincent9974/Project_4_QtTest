#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "protocal.h"

#include <QMessageBox>
#include <QProgressBar>
#include <QTimer>
#include <QDateTime>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QTimer* timer = new QTimer(this);
    timer->start(1000);
    connect(timer, &QTimer::timeout,
            this, &MainWindow::updateTime);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString time = currentTime.toString("yyyy-MM-dd HH:mm:ss");

    // 设置标签的文本为当前时间
    ui->label_time->setText(time);
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

    receiveThread = new ReceivePack(serialPort);
    receiveThread->start();

    //添加信号槽:接受线程发信号
    connect(receiveThread, &ReceivePack::receiveResponsePack,
            this, &MainWindow::updateData);

}

void MainWindow::updateData(char cmd, char param, int data)
{


    switch(cmd)
    {
    case ZHU_JI_WEN_DU_RSP:
        ui->label_temp->setText(QString::number(data));
        break;
    case ZHOU_SU_DU_RSP:
    {
        QLabel* labels[2] = {ui->label_RPM_main, ui->label_RPM_sub};
        if(param != 1 && param !=2) break;
        labels[param - 1]->setText(QString::number(data));
        break;
    }
    case GANG_YOU_LIANG_RSP:
    {
        QLabel* labels[3] = {ui->label_fuel1, ui->label_fuel2, ui->label_fuel3};
        if(param < 1 || param > 3)
        {
            break;
        }
        labels[param - 1]->setText(QString::number(data) + "L");
        break;
    }
    case YA_LI_CHANG_RSP:
    {
        QWidget* widgets[5][2] = {
            {ui->progressBar_tank1, ui->label_tank1},
            {ui->progressBar_tank2, ui->label_tank2},
            {ui->progressBar_tank3, ui->label_tank3},
            {ui->progressBar_tank4, ui->label_tank4},
            {ui->progressBar_tank5, ui->label_tank5},
            //{ui->progressBar_arm, ui->label_arm}

        };
        if(param < 1 || param > 5) break;
        QProgressBar* bar = (QProgressBar*)widgets[param - 1][0];
        bar->setValue(data);
        QLabel* label = (QLabel*) widgets[param -1][1];
        label->setText(QString::number(data));
    }

    case JI_XIE_BI_RSQ:
    {
        ui->progressBar_arm->setValue(data);
        ui->label_arm->setText(QString::number(data));
        break;
    }

    }
}
