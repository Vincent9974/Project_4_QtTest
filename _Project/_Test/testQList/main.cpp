#include <QCoreApplication>
#include <qDebug>
#include <QLinkedList>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    QList<int> list;
    list << 1 << 2 << 3 << 4
         << 5 << 6 << 7 << 8;
    list.append(9);
    list.append(10);

    qDebug() << list;

    qDebug() << list[2];
    qDebug() << list.at(2);
    qDebug() << list.contains(8);
    qDebug() << list.size();

    list.replace(5,66);
    list[0] = 100;
    qDebug() << list;

    QList<int> monList;
    QMutableListIterator<int> it_mtw(monList);
    for(int i =0; i < 12; i++)
    {
        it_mtw.insert(i);
    }
    qDebug() << "初始化后数据反遍历";
    for(it_mtw.toBack();it_mtw.hasPrevious();)
    {
        qDebug() << it_mtw.previous();
    }

    qDebug() << "初始化数据正遍历";
    for(it_mtw.toFront();it_mtw.hasNext();)
    {
        qDebug() << it_mtw.next();
    }


    for(it_mtw.toFront();it_mtw.hasNext();)
    {
        int month = it_mtw.next();
        if(month ==0 )
            it_mtw.remove();
        if(month == 11)
            it_mtw.setValue(12);
    }

    qDebug() << "初始化数据正遍历";
    for(it_mtw.toFront();it_mtw.hasNext();)
    {
        qDebug() << it_mtw.next();
    }

    QLinkedList<QString> weekendList;
    for(int j=1; j < 8; j++)
    {
        weekendList << QString("%1%2").arg("星期").arg(j);
    }

    QLinkedListIterator<QString> it_wr(weekendList);
    for(it_wr.toFront();it_wr.hasNext();)
        qDebug() << it_wr.next();


    return a.exec();
}
