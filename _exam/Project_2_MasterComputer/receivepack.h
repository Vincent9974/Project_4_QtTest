#ifndef RECEIVEPACK_H
#define RECEIVEPACK_H

#include <QObject>
#include <QThread>
#include <QSerialPort>



class ReceivePack : public QThread{
    Q_OBJECT
public:
    ReceivePack(QSerialPort* port);
    void run() override;

signals:
    void receiveResponsePack(char cmd, char param, int data);

private:
    QSerialPort* serialPort;

    bool parsePack(unsigned char pack[], int size, char* cmd, char* param, int* data);
};

#endif // RECEIVEPACK_H
