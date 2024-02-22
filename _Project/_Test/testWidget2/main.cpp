#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w1;
//    w1.setWindowTitle("w1窗体");
//    w1.show();

//    Widget w2;
//    w2.setWindowTitle("w2窗体");
//    w2.setWindowModality(Qt::ApplicationModal);
//    w2.show();

    Widget w3;
    w3.setWindowTitle("w3窗体");
    w3.show();


    return a.exec();
}
