#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(QObject* parent = nullptr);
    void stop();

protected:
    void run() override; //启动线程

private:
    bool m_isStopped;
};

#endif // MYTHREAD_H
