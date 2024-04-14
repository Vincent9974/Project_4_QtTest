#ifndef SENDPACK_H
#define SENDPACK_H

#include <QObject>
#include <QThread>
#include <QtSerialPort/QSerialPort>


class SendPack : public QThread
{
public:
    SendPack(QSerialPort* port);
    void run() override;

private:
    QSerialPort* serialPort;
    bool makePack(char cmd, char parm, char data[], char *pack);
};

#endif // SENDPACK_H
