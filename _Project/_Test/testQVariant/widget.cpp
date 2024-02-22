#include "widget.h"
#include <QDebug>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVariant vNum(100);
    qDebug() << vNum.toInt();

    QVariant vPI(3.1415);
    qDebug() << vPI.toFloat();

    QVariant vStr("hello");
    qDebug() << vStr.toString();

    QVariant vb(true);
    qDebug() << vb.toBool();

    QColor c = QColor(Qt::red);
    QVariant vC = c;
    qDebug() << vC.type();
    qDebug() << vC.value<QColor>();

    QVariant vss = vStr;
    qDebug() << vss.canConvert(QVariant::Int);
    qDebug() << vss.toString();


}

Widget::~Widget()
{
}

