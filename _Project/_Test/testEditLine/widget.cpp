#include "widget.h"
#include "ui_widget.h"
#include <QLineEdit>
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &Widget::showInput);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::showInput()
{
    qDebug() << ui->lineEdit ->text() << ui->lineEdit->displayText();
}

