#include "widget.h"
#include "ui_widget.h"
#include <QMovie>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->textLabel->setText("label文本显示,文字....");
    ui->numLabel->setNum(3.1415926);

    ui->picLabel->setPixmap(QPixmap("21.jpg"));

    QMovie* movie = new QMovie("21.gif");
    ui->gifLabel->setMovie(movie);
    ui->gifLabel->setScaledContents(true);
    movie->start();


}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_4_toggled(bool checked)
{
    qDebug() << "按钮按下" << checked;
}

void Widget::on_radioButton_2_toggled(bool checked)
{
    qDebug() << "按钮男按下" << checked;
}

void Widget::on_radioButton_3_toggled(bool checked)
{
    qDebug() << "按钮女按下" << checked;
}
