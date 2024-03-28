#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int num = 255;
    qDebug("十进制: %d", num);

    qDebug("八进制: %o", num);

    qDebug("十六进制: %x", num);

    qreal PI =3.1415;
    qDebug("圆周率: %f",PI);



    qreal price = 50000;
    qDebug("房价: %e", price);
    qDebug() << "房价:" << price;

    int rate = 95;
    qDebug("%d%%", rate); //两个百分号打印本身

    QString ss("我的。。。");
    qDebug() << ss;

    qDebug().noquote() <<ss;
    qDebug().quote() << ss;

    qDebug() << "[" << "你好" << "]";
    qDebug().nospace() << "[" << "你好" << "]";
    qDebug().space() << "[" << "你好" << "]";



    return a.exec();
}
