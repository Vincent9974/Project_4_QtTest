#include <QCoreApplication>
#include <QMap>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QMap<QString,QString> infoMap;

    //添加数据
    infoMap.insert("数据库","001");
    infoMap.insert("计算机网络","002");
    infoMap.insert("数据结构","003");
    infoMap.insert("机组","004");

    infoMap["编译原理"] = "005";
    qDebug() << "数据库:" << infoMap["数据库"];

    qDebug() << "数据库:" << infoMap.value("数据库");

    qDebug() << "001:" << infoMap.key("001");


    QMapIterator<QString,QString> it_r(infoMap);
    for(it_r.toFront();it_r.hasNext();)
    {
        it_r.next();
        qDebug() << it_r.key() <<":" <<it_r.value();
    }

    QMutableMapIterator<QString,QString> it_rw(infoMap);


    QMap<QString,QString> wMap;
    wMap.insert("spring","15℃");
    wMap.insert("summer","35℃");
    wMap.insert("autumn","23℃");
    wMap.insert("winter","-5℃");

    QMap<QString,QString>::const_iterator i_r;
    i_r = wMap.constBegin();

    qDebug() << endl << "初始化季节遍历:" ;
    for( ;i_r != wMap.constEnd(); ++i_r)
    {
        qDebug() << i_r.key() << ":" << i_r.value();
    }

    QMap<QString,QString>::iterator i_rw;
    i_rw = wMap.find("spring");
    if(i_rw!=wMap.end())
        i_rw.value() = "15℃";

    i_rw = wMap.begin();
    for( ;i_rw != wMap.end(); ++i_rw)
    {
        qDebug() << i_rw.key() << ":" << i_rw.value();
    }

    return a.exec();
}
