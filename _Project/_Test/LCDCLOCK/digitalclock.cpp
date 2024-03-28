#include "digitalclock.h"
#include <QTimer>
#include <QTime>
#include <QMouseEvent>

DigitalClock::DigitalClock(QWidget *parent) :QLCDNumber(parent)
{
    //设置蓝色背景
    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::blue);
    setPalette(p);

    //无边框窗体风格
    setWindowFlags(Qt::FramelessWindowHint);

    //窗体透明度
    setWindowOpacity(0.5);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
            this,  &DigitalClock::showTime);
    timer->start(1000); //周期为1000毫秒

    showTime();
    resize(150, 60);
    m_showColon = true;
}

void DigitalClock::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_dragPosition = event->globalPos()
                         - frameGeometry().topLeft();
        event->accept();
    }
    if(event->button() == Qt::RightButton)
    {
        close();
    }
}

void DigitalClock::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}


void DigitalClock::showTime()
{
    QTime time = QTime::currentTime();
    QString strTime = time.toString("hh:mm");
    if(m_showColon)
    {
        strTime[2] = ':';
    }
    else
    {
        strTime[2] = ' ';
    }

    display(strTime);
    m_showColon = !m_showColon;
}
