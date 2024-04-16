#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include "mainwindow.h"

namespace Ui {
class Server;
}

class Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

private slots:
    // 用于处理新的客户端连接
    void onNewConnection();

    void handleClientDisconnected();



private:
    Ui::Server *ui;
    QTcpServer *m_server;
    QTcpSocket *m_client;


    void handleClient(QTcpSocket *client);
};

#endif // SERVER_H
