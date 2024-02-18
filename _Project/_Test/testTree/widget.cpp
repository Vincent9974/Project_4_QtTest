#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug() << "Weidget 构造!" << this;
}

Widget::~Widget()
{
    delete ui;
    qDebug() << "Weidget 析构!" << this;
}

