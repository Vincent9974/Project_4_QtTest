#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_tcpSocket = new QTcpSocket(this);


    //socket做数据处理
    connect(m_tcpSocket,&QTcpSocket::readyRead,
            this,&Widget::onReadMessage);

    connect(m_tcpSocket, SIGNAL(SocketError),
            this,SLOT(onDisplayError(QAbstractSocket::SocketError)));

    ui->hostLineEdit->setText("127.0.0.1");
    ui->portLineEdit->setText(QString::number(gTcpPort));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::onReadMessage()
{
    QByteArray bt;
    bt.resize(m_tcpSocket->bytesAvailable());
    m_tcpSocket->read(bt.data(), bt.size());

    ui->label_4->setText(bt);
}

void Widget::onDisplayError(QAbstractSocket::SocketError e)
{
    qDebug() << "SocketError:" << e << endl
             << m_tcpSocket->errorString();
}

void Widget::on_pushButton_2_clicked()
{
    m_tcpSocket->abort();

    //connectToHost(IP, Port)
    m_tcpSocket->connectToHost(ui->hostLineEdit->text(),
                               ui->portLineEdit->text().toInt());
}

void Widget::on_pushButton_clicked()
{
    m_tcpSocket->write(ui->sendLineEdit->text().toUtf8());
}
