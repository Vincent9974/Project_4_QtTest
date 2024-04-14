#include "sendpack.h"
#include "protocol.h"
#include <QDebug>

SendPack::SendPack(QSerialPort* port)
{
    serialPort = port;
}

void SendPack::run()
{
    unsigned char cmdAndParm[][2]
    {
        {tempQuery, 0},
    };

    char pack[9];
    char data[4] = {0, 0, 0, 0};
    //发包
    int cmdCount = sizeof(cmdAndParm) / sizeof(cmdAndParm[0]);
    while (1) {
        for(int i = 0; i<cmdCount; i++)
        {
            makePack(cmdAndParm[i][0],
                     cmdAndParm[i][1],
                     data,
                     pack);

            int ret = serialPort->write(pack, sizeof(pack));
            qDebug() << "send:" << ret << "bytes";
            serialPort->waitForBytesWritten(500);
            QThread::msleep(3000);
        }
    }
}

bool SendPack::makePack(char cmd, char param, char data[], char *pack)
{
    if(!pack) return false;

    pack[0] = 0xEF;
    pack[1] = cmd;
    pack[2] = param;

    pack[3] = data[0];
    pack[4] = data[1];
    pack[5] = data[2];
    pack[6] = data[3];

    //使用偶校验
    int count = 0;

    for(int k =1; k<=6; k++)
    {
        char byte = pack[k];

        for(int i=0; i<8; i++)
        {
            if(byte & 1) count++;
            byte  >>=1;
        }
    }

    if(count & 1) //下位机偶校验
    {
        pack[7] = 1;
    }
    else
    {
        pack[7] = 0;
    }

    pack[7] =0xFE;
    return true;
}
