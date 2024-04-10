#include "widget.h"
#include "ui_widget.h"

extern int gNums;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    gNums = 0;
    m_myThread1.start();
    m_myThread2.start();
    m_myThread3.start();
}

void Widget::on_pushButton_2_clicked()
{
    m_myThread1.stop();
    m_myThread2.stop();
    m_myThread3.stop();
}
