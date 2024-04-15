#ifndef SENDPACK_H
#define SENDPACK_H

#include <QObject>
#include <QThread>
#include <QSerialPort>


class SendPack : public QThread
{
public:
    SendPack(QSerialPort* port);
    void run() override;
    bool makePack(char cmd, char parm, char data[], char *pack);

private:
    QSerialPort* serialPort;
};

#endif // SENDPACK_H
