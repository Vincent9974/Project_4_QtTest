#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QGraphicsOpacityEffect>
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置样式, 按钮设置黄色背景色
//    ui->pushButton->setStyleSheet("background:yellow");
//    ui->pushButton->setStyleSheet("color:red");
//    setStyleSheet("QPushButton{background:yellow;color:red}");

//    ui->horizontalSlider->setStyleSheet("background:blue");

    // 窗口不透明度
//    setWindowOpacity(1);

    //部件不透明,窗体透明
//    setWindowFlags(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground);

    //部件设置透明
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;

    opacityEffect->setOpacity(0.1);
    ui->label->setGraphicsEffect(opacityEffect);

    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setColor(QColor(100,100,100));
    shadowEffect->setBlurRadius(20);
    shadowEffect->setOffset(20);
    ui->label->setGraphicsEffect(shadowEffect);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(255, 255, 255, 200));
}

