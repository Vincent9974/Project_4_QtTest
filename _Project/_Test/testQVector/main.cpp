#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVector<QString> vStars;
    vStars << "斯凯";
    vStars <<"一决" << "瑞纳";
    vStars.append("捷风");
    vStars.prepend("蝰蛇");
    vStars.insert(1,"贤者");
    qDebug() << vStars;

    vStars.replace(0,"火男");
    qDebug() << vStars;

    vStars.removeAll("火男");
    qDebug() << vStars;

    qDebug() << vStars.contains("贤者");
    qDebug() << vStars[2];

    QVectorIterator<QString> it_sr(vStars);
    for(it_sr.toFront();it_sr.hasNext();)
        qDebug() << it_sr.next();

    QMutableVectorIterator<QString> it_srw(vStars);
    for(it_sr.toFront();it_srw.hasNext();)
    {
        QString s = it_srw.next();
        if(!QString::compare(s,"贤者"))
        {
            it_srw.setValue("魏玲莹");
        }
    }
    qDebug() << "贤者修改后:";
    for(it_srw.toFront();it_srw.hasNext();)
        qDebug() << it_srw.next();



    return a.exec();
}
