#ifndef RECEIVEPACK_H
#define RECEIVEPACK_H

#include <QObject>
#include <QThread>
#include <QtSerialPort/QSerialPort>



class ReceivePack : public QThread
{
public:
    ReceivePack(QSerialPort* port);
};

#endif // RECEIVEPACK_H
