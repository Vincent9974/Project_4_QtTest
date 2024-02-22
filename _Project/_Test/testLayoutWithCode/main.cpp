#include "testlayout.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestLayout w;
    w.show();
    return a.exec();
}
