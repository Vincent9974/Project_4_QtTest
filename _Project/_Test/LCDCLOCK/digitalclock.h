#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H
#include <QLCDNumber>

class DigitalClock : public QLCDNumber
{
    Q_OBJECT
public:
    DigitalClock(QWidget* parent = 0);
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private slots:
    void showTime(); //显示当前时间
private:
    QPoint m_dragPosition; //保存鼠标点相应电子钟表窗体左上角的偏移值
    bool m_showColon; // 钟表是否显示闪烁":"
};

#endif // DIGITALCLOCK_H
