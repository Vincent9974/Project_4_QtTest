#include "mylayout.h"
#include <QDebug>

MyLayout::MyLayout(QWidget *parent)
{
    qDebug() << "MyLayout 构造"<< this;
}

MyLayout::~MyLayout()
{
    qDebug() << "MyLayout 析构"<< this;
}
