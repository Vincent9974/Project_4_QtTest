#include "mainwindow.h"
#include "server.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Server s;

    w.show();
    s.show();



    w.setGeometry(100, 100, w.width(), w.height());
    s.setGeometry(100, 100 + w.height(), s.width(), s.height());

    return a.exec();
}
