#include "widget.h"
#include "mylabel.h"
#include "mylayout.h"
#include "myradiobutton.h"
#include <QObjectList>
#include <QDebug>
#include <QObject>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    MyLabel *mylabel = new MyLabel(&w);
    MyRadioButton *myBtn = new MyRadioButton(&w);
    MyLayout *mylayout = new MyLayout(&w);

    mylabel->setText("子标签");
    myBtn->setText("子按钮");

    mylayout->addWidget(mylabel,0 ,0);
    mylayout->addWidget(myBtn, 1, 0);
    mylayout->addWidget(myBtn,2,0);


    w.setLayout(mylayout);
    w.show();

    const QObjectList list = w.children();
    qDebug() << "w.children";
    foreach(QObject* obj,list)
        qDebug() << obj;

    return a.exec();
}
