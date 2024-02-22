#include "dialog.h"

#include <QApplication>
#include "templedialog.h"
#include <qDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    Dialog w1;
//    w1.setWindowTitle("w1");
////    w1.setWindowModality(Qt::ApplicationModal);
//    w1.show();

//    Dialog w2;
//    w2.setWindowTitle("w2");
//    w2.setModal(true);
//    w2.show();

//    Dialog w3;
//    w3.setWindowTitle("w3");
//    w3.show();

    int res;
    TempleDialog tDialog;
    //tDialog.show();
    res = tDialog.exec();
    qDebug() << res;

    return a.exec();
}
