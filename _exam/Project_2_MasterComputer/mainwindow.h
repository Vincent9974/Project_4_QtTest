#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include "sendpack.h"
#include "receivepack.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateTime();

public:
    void monitor();
    void updateData(char cmd, char param, int data);


private:
    Ui::MainWindow *ui;
    QSerialPort* serialPort; //串口
    SendPack* senderThread; //串口发送线程
    ReceivePack* receiveThread; //串口接受线程
};

#endif // MAINWINDOW_H
