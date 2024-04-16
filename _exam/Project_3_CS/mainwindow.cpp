#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTcpSocket>
#include <QMessageBox>
#include <QPushButton>
#include <QJsonObject>
#include <QByteArray>
#include <QJsonDocument>
#include <QActionGroup>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    socket(new QTcpSocket(this))
{
    ui->setupUi(this);
    this->setWindowTitle("client");

    m_actionGroup = new QActionGroup(this);
    m_actionGroup->addAction(ui->actionconfig1);
    m_actionGroup->addAction(ui->actionconfig2);
    m_actionGroup->addAction(ui->actionconfig3);


    socket->connectToHost("127.0.0.1", gTcpPort);

    // 设置 socket 连接
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::onSocketReadyRead);

    // 连接 Load 和 Save 动作到槽函数
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::loadSettings);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveSettings);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadSettings()
{
    QAction* checkedAction = m_actionGroup->checkedAction();
    if(checkedAction == ui->actionconfig1)
    {
        // 发送请求到服务器config1
        socket->write("LOAD");
        qDebug() << "LOAD1 emit";
    }
    else if(checkedAction == ui->actionconfig2)
    {
        // 发送请求到服务器config2
        socket->write("LOAD2");
        qDebug() << "LOAD2 emit";
    }
    else if(checkedAction == ui->actionconfig3)
    {
        // 发送请求到服务器config3
        socket->write("LOAD3");
        qDebug() << "LOAD3 emit";
    }
    else
    {
        QMessageBox::information(this,"提示","请选择菜单栏中Admin中的config");
    }
}

void MainWindow::saveSettings()
{
    QJsonObject json = collectSettings();

    if(ui->lineEditAccount->text() =="" || ui->lineEditPassword->text() =="")
    {
        QMessageBox::information(this,"提示","有空内容");
        return;
    }

    // 序列化 JSON 数据
    QJsonDocument doc(json);
    QByteArray jsonData = doc.toJson();

    // 将 JSON 数据发送到服务器
    socket->write(jsonData);
    ui->lineEditAccount->setText("");
    ui->lineEditPassword->setText("");
}

void MainWindow::onSocketReadyRead()
{
    // 读取来自服务器的数据
    QByteArray responseData = socket->readAll();

    //qDebug() << "readData:" << responseData ;

    // 将 JSON 数据解析为对象
    QJsonDocument doc = QJsonDocument::fromJson(responseData);
    QJsonObject json = doc.object();

    //qDebug() << "json:" << json ;

    // 更新界面
    updateUIFromJson(json);
}

void MainWindow::updateUIFromJson(const QJsonObject &json) {
    // 根据 JSON 数据更新界面元素

    ui->lineEditAccount->setText(json["key1"].toString());
    ui->lineEditPassword->setText(json["key2"].toString());
}


QJsonObject MainWindow::collectSettings()
{
    QJsonObject json;
    QJsonObject emptyJsonObject;

    json["key1"] = ui->lineEditAccount->text();
    json["key2"] = ui->lineEditPassword->text();

    if(m_actionGroup->checkedAction() != nullptr)
    {
        json["config"] = m_actionGroup->checkedAction()->objectName();
        return json;
    }
    else
    {
        QMessageBox::information(this,"提示","save前请选择config");
        return emptyJsonObject;
    }
}



