#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString s0 = "Hello"; //"hello"的引用计数1
    QString s1 = s0; //"hello"的引用计数2
    QString s2 = s0; //"hello"的引用计数3

    s2 = "hi";
    QString s3 = s0;
    QString s4 =s2;
    QString s5 =s2;

    QString str("cpp");
    qDebug() << str;

    QString s00 = "hello";
    qDebug() << s00;
    QString s11 = s00;
    qDebug() << s11;

    QChar data[5] = {'h','e','l','l','o'};
    QString s44(data,5);
    qDebug() << s44;
    qDebug() << sizeof(QChar);
    qDebug() << sizeof(char);

    QString strAge("18");
    int age = strAge.toInt();
    qDebug() << strAge;
    qDebug() << age;

    QString strPI("3.14");
    float fPI = strPI.toFloat();
    qDebug() << strPI;
    qDebug() << fPI;

    int year = 1949;
    int year1 = 2020;
    float height = 1.83f;
    float width = 6.6f;

    QString strYear,strYear1,strHeight,strWidth;
    strYear = strYear.number(year);
    strYear1 = strYear.number(year1);
    strHeight = strYear.number(height);
    strWidth = strYear.number(width);

    qDebug() << strYear << strYear1;
    qDebug() << strHeight << strWidth;

    // const char* 转QString
    const char* hi = "hello world";
    QString strHi(hi);
    qDebug() << strHi;

    QString strTom = "Tom";
    QByteArray tomArray = strTom.toUtf8();
    const char* cTom = tomArray.data();
    qDebug() << cTom;
    qDebug() << tomArray;

    QString strTime = "1949-10-01 10:00:00";
    QDateTime dtTime = QDateTime::fromString(strTime,"yyyy-MM-dd hh:mm:ss");
    qDebug() << dtTime;

    QDateTime curTime = QDateTime::currentDateTime();
    qDebug() << curTime;
    QString strCurTime = curTime.toString("yyyy-MM-dd hh:mm:ss");
    qDebug() << strCurTime;

    QString s = "小红书";
    s += "用户";
    qDebug() << s;
    s.append("momo");
    qDebug() << s;

    QString ss0,ss1;
    ss0.sprintf("%d%s%f",10,"年",1.1);
    qDebug() << ss0;

    QString strXHS = QString("%1%2%3").arg("小红书").arg("用户").arg("momo");
    qDebug() << strXHS;


    QString cat = "chibi";
    qDebug() << cat.at(1);

    QString sYear = "距今年前";
    qDebug() << sYear.insert(2,"100");

    qDebug()<<sYear.prepend("--");
    qDebug()<<sYear.replace(4,3,"500");

    sYear = "   " +sYear+ "   ";
    qDebug()<<sYear;

    qDebug()<<sYear.trimmed();
    QString sFish = "   salmon Fish  oishi  !";
    qDebug()<<sFish.simplified();


    qDebug() << QString::compare("Tom", "tom", Qt::CaseSensitive);
    qDebug() << QString::compare("Tom", "tom", Qt::CaseInsensitive);

    QString strTime1949 = "1949/10/01";
    QStringList timeList = strTime1949.split('/');
    foreach(QString ss,timeList)
        qDebug() << ss;

    QString sFriends = "Tom and Jerry";
    qDebug() << sFriends.mid(4,5);

    QStringList weekList;
    weekList << "周一" << "周二" << "周三";
    weekList << "周四";
    weekList << "周五";
    weekList << "周六";
    weekList.append("周日");
    qDebug()<< weekList;

    //for
    qDebug()<< "for遍历";
    for(int i=0;i<weekList.size();i++)
        qDebug()<< weekList[i];

    qDebug()<< "foreach遍历";
    foreach(QString week,weekList)
        qDebug()<< week;

    qDebug()<< "STL遍历";
    QStringList::iterator it = weekList.begin();
    for(;it!=weekList.end();it++)
        qDebug()<< *it;

    qDebug()<< weekList.contains("周八");
    weekList.insert(0,"周0");
    qDebug()<< weekList;

    weekList.removeFirst();
    qDebug()<< weekList;

    weekList.append("周八");
    qDebug()<< weekList;

    weekList.removeAt(7);
    qDebug()<< weekList;

    weekList.removeOne("周一");
    qDebug()<< weekList;

    weekList.clear();
    qDebug()<< weekList;

    return a.exec();
}
