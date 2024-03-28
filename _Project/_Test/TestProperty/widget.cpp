#include "widget.h"
#include "ui_widget.h"
#include "mypropertyclass.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    MyPropertyClass *mypC = new MyPropertyClass;
    MyPropertyClass *mypC2 = new MyPropertyClass;
    connect(mypC,SIGNAL(maskChanged(QString)),this,SLOT(maskChanged(QString)));
    mypC->setMask("1000000000亿个口罩");
    qDebug() << "当前口罩属性：" << mypC->mask();

    QObject* obj = mypC;
    qDebug() << "obj进行属性的读取：" << obj->property("mask").toString();

    obj->setProperty("mask","2000000000亿个口罩");
    qDebug() << "obj进行第二次属性的读取：" << obj->property("mask").toString();

    qDebug() << "mypC2读取属性：" << mypC2->mask();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::maskChanged(QString str)
{
    qDebug() << "新的口罩库存：" << str;
}
