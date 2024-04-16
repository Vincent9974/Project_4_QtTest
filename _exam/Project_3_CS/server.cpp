#include "server.h"
#include "ui_server.h"
#include "mainwindow.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QMap>

extern const int gTcpPort;

Server::Server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    this->setWindowTitle("Server");
    ui->lineEdit1->setReadOnly(true);
    ui->lineEdit2->setReadOnly(true);

    m_server = new QTcpServer(this);


    // 监听特定端口
    if (!m_server->listen(QHostAddress::Any, gTcpPort))
    {
        qDebug() << m_server->errorString();
        close();
    }

    qDebug() << "Server listening on port " << QString::number(gTcpPort);

    // 连接 newConnection 信号到槽函数
    connect(m_server, &QTcpServer::newConnection,
            this, &Server::onNewConnection);




}

Server::~Server()
{

}

void Server::onNewConnection()
{
    // 接受新的客户端连接
    QTcpSocket* client = m_server->nextPendingConnection();
    if (client)
    {
    connect(client, &QTcpSocket::readyRead,
            [this, client]() {
        handleClient(client);
    });
    connect(client, &QTcpSocket::disconnected, this,
            &Server::handleClientDisconnected);
    }

//    if(m_client)
//    {
//        connect(m_client, &QTcpSocket::readyRead,
//                this, &Server::handleClient);
    //    }
}

void Server::handleClientDisconnected()
{
    qDebug() << "Client disconnected";

    // 在这里，你可以执行客户端断开连接时需要的操作
    // 例如，释放资源、清理数据、更新UI等

    // 清除客户端指针
//    m_client->deleteLater();
//    m_client = nullptr;
}




void Server::handleClient(QTcpSocket *client)
{

    // 读取客户端请求
    QByteArray request = client->readAll();

    qDebug() << "request" << QString(request);

    // 定义请求类型和对应的文件路径的映射
    QMap<QString, QString> requestToFileMap = {
        {"LOAD", "/config.json"},
        {"LOAD2", "/config2.json"},
        {"LOAD3", "/config3.json"}
    };

    if (requestToFileMap.contains(request)) {
        qDebug() << "Load success:";

        // 获取对应的文件路径
        QString filePath = QDir::currentPath() + requestToFileMap[request];

        QFile file(filePath);

        // 打开文件读取数据
        if (file.open(QFile::ReadOnly)) {
            QByteArray data = file.readAll();
            qDebug() << "data" << data;
            file.close();

            // 发送数据到客户端
            client->write(data);
        } else {
            qWarning() << "Failed to open config file";
        }
    }

     else {
        // 处理保存数据请求
        QJsonDocument doc = QJsonDocument::fromJson(request);
        QJsonObject json = doc.object();
        ui->labelJson->setText(request);

        qDebug() << "json:" << json;

        QFile file; // 定义文件对象

        // 根据 config 的值确定文件路径
        if (json.value("config") == "actionconfig1") {
            qDebug() << "actionconfig1";
            ui->lineEdit1->setText(json.value("key1").toString());
            ui->lineEdit2->setText(json.value("key2").toString());
            file.setFileName(QDir::currentPath() + "/config.json");
        } else if (json.value("config") == "actionconfig2") {
            qDebug() << "actionconfig2";
            ui->lineEdit1->setText(json.value("key1").toString());
            ui->lineEdit2->setText(json.value("key2").toString());
            file.setFileName(QDir::currentPath() + "/config2.json");
        } else if (json.value("config") == "actionconfig3") {
            qDebug() << "actionconfig3";
            ui->lineEdit1->setText(json.value("key1").toString());
            ui->lineEdit2->setText(json.value("key2").toString());
            file.setFileName(QDir::currentPath() + "/config3.json");
        }

        // 打开并保存请求数据
        if (file.open(QFile::WriteOnly)) {
            file.write(request);
            file.close();
        } else {
            qWarning() << "Failed to open config file";
        }
    }

    // 断开客户端连接
    //client->disconnectFromHost();
}

//void Server::handleClient()
//{
//    // 使用全局变量 m_client 而不是函数参数 client

//    QTcpSocket *client = m_client;

//    // 读取客户端请求
//    QByteArray request = client->readAll();

//    qDebug() << "request" << QString(request);

//    // 定义请求类型和对应的文件路径的映射
//    QMap<QString, QString> requestToFileMap = {
//        {"LOAD", "/config.json"},
//        {"LOAD2", "/config2.json"},
//        {"LOAD3", "/config3.json"}
//    };

//    if (requestToFileMap.contains(request)) {
//        qDebug() << "Load success:";

//        // 获取对应的文件路径
//        QString filePath = QDir::currentPath() + requestToFileMap[request];

//        QFile file(filePath);

//        // 打开文件读取数据
//        if (file.open(QFile::ReadOnly)) {
//            QByteArray data = file.readAll();
//            qDebug() << "data" << data;
//            file.close();

//            // 发送数据到客户端
//            client->write(data);
//        } else {
//            qWarning() << "Failed to open config file";
//        }
//    } else {
//        // 处理保存数据请求
//        QJsonDocument doc = QJsonDocument::fromJson(request);
//        QJsonObject json = doc.object();
//        ui->labelJson->setText(request);

//        qDebug() << "json:" << json;

//        QFile file; // 定义文件对象

//        // 根据 config 的值确定文件路径
//        if (json.value("config") == "actionconfig1") {
//            qDebug() << "actionconfig1";
//            ui->lineEdit1->setText(json.value("key1").toString());
//            ui->lineEdit2->setText(json.value("key2").toString());
//            file.setFileName(QDir::currentPath() + "/config.json");
//        } else if (json.value("config") == "actionconfig2") {
//            qDebug() << "actionconfig2";
//            ui->lineEdit1->setText(json.value("key1").toString());
//            ui->lineEdit2->setText(json.value("key2").toString());
//            file.setFileName(QDir::currentPath() + "/config2.json");
//        } else if (json.value("config") == "actionconfig3") {
//            qDebug() << "actionconfig3";
//            ui->lineEdit1->setText(json.value("key1").toString());
//            ui->lineEdit2->setText(json.value("key2").toString());
//            file.setFileName(QDir::currentPath() + "/config3.json");
//        }

//        // 打开并保存请求数据
//        if (file.open(QFile::WriteOnly)) {
//            file.write(request);
//            file.close();
//        } else {
//            qWarning() << "Failed to open config file";
//        }
//    }

//    // 断开客户端连接
//    client->disconnectFromHost();
//}



