#include "HelloWorld.h"

#include <QApplication>
#include <QDebug>
#include <QImage>

#pragma comment(lib, "user32.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HelloWorld w;
    w.show();
    return a.exec();
}