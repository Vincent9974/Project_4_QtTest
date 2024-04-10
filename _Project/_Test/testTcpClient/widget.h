#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>

const int gTcpPort = 8888;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void onReadMessage();
    void onDisplayError(QAbstractSocket::SocketError);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket* m_tcpSocket;
};

#endif // WIDGET_H
