#include "mylabel.h"
#include <QDebug>


MyLabel::MyLabel(QWidget *parent):QLabel(parent)
{
    qDebug() << "Mylabel 构造"<< this;
}

MyLabel::~MyLabel()
{
    qDebug() << "Mylabel 析构"<< this;
}
