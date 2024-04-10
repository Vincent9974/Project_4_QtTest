#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_receiver = new QUdpSocket(this);

    //绑定
    m_receiver->bind(6666,QUdpSocket::ShareAddress);

    //有数据来就处理
    connect(m_receiver,&QUdpSocket::readyRead,
            this, &Widget::ProcessData);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::ProcessData()
{
    QString strData;

    //有未处理的数据报
   while(m_receiver->hasPendingDatagrams())
   {
       QByteArray dataGram;
       dataGram.resize(m_receiver->pendingDatagramSize());
       m_receiver->readDatagram(dataGram.data(), dataGram.size());

       ui->label_2->setText(dataGram);
   }
}
