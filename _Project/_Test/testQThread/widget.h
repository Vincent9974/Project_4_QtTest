#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mythread.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    MyThread m_myThread1, m_myThread2,m_myThread3;
};

#endif // WIDGET_H
