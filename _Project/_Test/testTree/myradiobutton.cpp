#include "myradiobutton.h"
#include <QDebug>



MyRadioButton::MyRadioButton(QWidget *parent)
{
    qDebug() << "MyButton 构造"<< this;
}

MyRadioButton::~MyRadioButton()
{
    qDebug() << "MyButton 析构"<< this;
}
