#include "mythread.h"
#include <QDebug>
#include <QMutex>

int gNums = 0;
QMutex mutex; //互斥锁

MyThread::MyThread(QObject* parent): QThread(parent)
{
    m_isStopped = false;
}

void MyThread::stop()
{
    m_isStopped = false;
}

void MyThread::run()
{
    int i = 0;
    while(!m_isStopped && i++ <200000)
    {
        mutex.lock();
        qDebug() << QString("%1").arg(++gNums);
        mutex.unlock();
    }
}
