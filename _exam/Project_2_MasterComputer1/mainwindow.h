#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QGraphicsProxyWidget>
#include <QPixmap>
#include "sendpack.h"
#include "receivepack.h"

const int MAX_PRESSURE = 1200* 0.9;

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
    void setNeedleValue(double value);
    void on_pushButton_add_clicked();
    void on_pushButtonSub_clicked();

public:
    void monitor();
    void updateData(char cmd, char param, int data);
    void updateWarningLabel();



private:
    Ui::MainWindow *ui;
    QSerialPort* serialPort; //串口
    SendPack* senderThread; //串口发送线程
    ReceivePack* receiveThread; //串口接受线程

    bool pressureStatus[6] = {false,};
    QGraphicsProxyWidget* m_neddle; //报警针
    QPixmap pixNormalStaus;
    QPixmap pixWarningStatus;
    int pressThreshold = MAX_PRESSURE; // 大于该值就要告警
};

#endif // MAINWINDOW_H
