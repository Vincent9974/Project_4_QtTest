#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
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

public:
    void monitor();

private:
    Ui::MainWindow *ui;
    QSerialPort* serialPort; //串口
    SendPack* senderThread; //串口发送线程
    ReceivePack* receiveThread; //串口接受线程
};

#endif // MAINWINDOW_H
