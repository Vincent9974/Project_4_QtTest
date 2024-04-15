#include "sendpack.h"
#include "protocal.h"
#include <QDebug>
#include <queue>
#include <mutex>
#include <condition_variable>



SendPack::SendPack(QSerialPort* port)
{
    serialPort = port;
}

void SendPack::run()
{
    // 添加数据包队列、互斥锁和条件变量
    std::queue<std::pair<char, char>> sendQueue;
    std::mutex queueMutex;
    std::condition_variable queueCondition;

    unsigned char cmdAndParm[][2]
    {
        {ZHU_JI_WEN_DU_REQ, 0},
        {ZHOU_SU_DU_REQ, 1},
        {ZHOU_SU_DU_REQ, 2},
        {GANG_YOU_LIANG_REQ, 1},
        {GANG_YOU_LIANG_REQ, 2},
        {GANG_YOU_LIANG_REQ, 3},
        {YA_LI_CHANG_REQ, 1},
        {YA_LI_CHANG_REQ, 2},
        {YA_LI_CHANG_REQ, 3},
        {YA_LI_CHANG_REQ, 4},
        {YA_LI_CHANG_REQ, 5},
        {JI_XIE_BI_REQ, 0},
        {DONG_LI_GAN_SU_DU_SET_REQ, 0XF0},
        {DONG_LI_GAN_SU_DU_SET_RSP, 0X0F}
    };

    char pack[9];
    char data[4] = {0, 0, 0, 0};
    //发包
    int cmdCount = sizeof(cmdAndParm) / sizeof(cmdAndParm[0]);
    while (1) {

//        // 使用条件变量等待队列中有数据包
//        std::unique_lock<std::mutex> lock(queueMutex);
//        queueCondition.wait(lock, [] { return !sendQueue.empty(); });

//        // 从队列中取出数据包
//        auto request = sendQueue.front();
//        sendQueue.pop();

//        // 发送数据包
//        makePack(request.first, request.second, data, pack);
//        int ret = serialPort->write(pack, sizeof(pack));
//        qDebug() << "send:" << ret << " bytes";
//        serialPort->waitForBytesWritten(500);
//        QThread::msleep(300);



        for(int i = 0; i<cmdCount; i++)
        {
            makePack(cmdAndParm[i][0],
                     cmdAndParm[i][1],
                     data,
                     pack);

            int ret = serialPort->write(pack, sizeof(pack));
            qDebug() << "send:" << ret << "bytes";
            serialPort->waitForBytesWritten(500);
            QThread::msleep(300);
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

    pack[8] =0xFE; //包尾
    return true;
}
