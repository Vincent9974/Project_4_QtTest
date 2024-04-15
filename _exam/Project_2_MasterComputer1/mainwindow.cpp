#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "protocal.h"
#include "neddle.h"
#include <thread>

#include <QMessageBox>
#include <QProgressBar>
#include <QTimer>
#include <QDateTime>
#include <QGraphicsScene>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QTimer* timer = new QTimer(this);
    timer->start(1000);
    connect(timer, &QTimer::timeout,
            this, &MainWindow::updateTime);

    ui->pushButtonAdd->setStyleSheet(
                "QPushButton{"
                     "background-image:url(:res/add_normal.png);"
                     "padding:0;"
                     "border:0;"
                     "background-position:Center;}"
                "QPushButton:pressed{"
                     "background-image:url(:res/add_press.png);}"
                );

    ui->pushButtonSub->setStyleSheet(
                "QPushButton{"
                     "background-image:url(:res/sub_normal.png);"
                     "padding:0;"
                     "border:0;"
                     "background-position:Center;}"
                "QPushButton:pressed{"
                     "background-image:url(:res/sub_press.png);}"
                );

    //创建一个图像场景
    QGraphicsScene* scene = new QGraphicsScene();
    //设置场景的位置区域
    scene->setSceneRect(ui->graphicsView->rect());

    m_neddle = scene->addWidget(new neddle);

    //设置指针窗口在场景中的位置
    m_neddle->setPos(100,  103);
    m_neddle->setTransformOriginPoint(4, 0); //旋转原点在指针图片内部的(4,0)位置

    pixNormalStaus =  QPixmap(":/res/normal.png");
    pixWarningStatus =  QPixmap(":/res/warning.png");

    ui->graphicsView->setScene(scene);

    connect(ui->pushButtonAdd, &QPushButton::clicked,
            this, &MainWindow::on_pushButton_add_clicked);
    connect(ui->pushButtonSub, &QPushButton::clicked,
            this, &MainWindow::on_pushButtonSub_clicked);


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

void MainWindow::setNeedleValue(double value)
{
    if(value < 0) value = 0;
    else if(value > 120) value = 120;

    double rotateAngle = (double)((310.0 - 54.0) / 120) * value + 54.00;

    //微调
    if(value < 40) rotateAngle += 1;
    else if(40 < value) rotateAngle -= 2;

    m_neddle->setRotation(rotateAngle);
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
        bool warning = data >= pressThreshold;
        pressureStatus[param - 1] = warning;

        QProgressBar* bar = (QProgressBar*)widgets[param - 1][0];
        bar->setValue(data);


        // 报警,则设置 QProgressBar 的颜色
        if (data > MAX_PRESSURE) {
            // 设置红色
            bar->setStyleSheet("QProgressBar::chunk { background-color: red; }");
        } else {
            bar->setStyleSheet("");
        }

        QLabel* label = (QLabel*) widgets[param -1][1];
        label->setText(QString::number(data));
    }

    case JI_XIE_BI_RSQ:
    {
        ui->progressBar_arm->setValue(data);
        ui->label_arm->setText(QString::number(data));
        break;
    }

    case DONG_LI_GAN_SU_DU_SET_RSP:
    {
        setNeedleValue(data);
        break;
    }
    }

    updateWarningLabel();
}

void MainWindow::updateWarningLabel()
{
    if (pressureStatus[0] || pressureStatus[1] || pressureStatus[2] ||
        pressureStatus[3] || pressureStatus[4] || pressureStatus[5]) {
        ui->label_status->setPixmap(pixWarningStatus);
    } else {
        ui->label_status->setPixmap(pixNormalStaus);
    }
}

void MainWindow::on_pushButton_add_clicked()
{
//    char pack[9] = {0,};
//    senderThread->makePack(DONG_LI_GAN_SU_DU_SET_REQ, 0xF0, 0, pack);
//    int ret = serialPort->write(pack, sizeof(pack));
//    qDebug() << "send: " << ret << " bytes.";
}

void MainWindow::on_pushButtonSub_clicked()
{
//    char pack[9] = {0,};
//    senderThread->makePack(DONG_LI_GAN_SU_DU_SET_REQ, 0x0F, 0, pack);
//    int ret = serialPort->write(pack, sizeof(pack));
//    qDebug() << "send: " << ret << " bytes.";
}

