#include <QCoreApplication>
#include <QDebug>
#include <QRegularExpression>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QRegExp reg("a");
    qDebug() << "匹配字符本身:"
             << reg.exactMatch("abc")
             << reg.exactMatch("ab")
             << reg.exactMatch("a")
             << endl;

    QRegExp reg0("\\d*\\D{2}");
    qDebug() << "匹配数字:"
             << reg0.exactMatch("188cm")
             << reg0.exactMatch("188m")
             << reg0.exactMatch("72in")
             << endl;

    QRegExp rx("*.txt");
    rx.setPatternSyntax(QRegExp::Wildcard);
    qDebug() << "通配符:"
             << rx.exactMatch("License.txt")
             << rx.exactMatch("License.txt.bak")
             << endl;

    //匹配单词边界
    QRegExp reg1;
    reg1.setPattern("\\b(hello|Hello)\\b");
    qDebug() << "匹配多个单词:"
             << reg1.indexIn("helloEveryone!")
             << reg1.indexIn("Hello everyone")
             << endl;

    //捕获匹配的文本
    QRegExp regHeight("(\\d+)(?:\\s*)(cm|inch)");
    qDebug() << regHeight.indexIn("Yaoming 226cm");

    QRegExp reg2;
    reg2.setPattern("面(?=包)");
    QString str = "面条包, 面包";
    qDebug() << str;
    str.replace(reg2,"意大利");
    qDebug() << str;

    QRegularExpression regExp("hello");
    qDebug() << "QRegularExpression 匹配字符:"
             << regExp.match("hello world!");
    regExp.setPattern("[A-Z]{3,8}");
    regExp.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
    qDebug() << "大小写不敏感匹配:"
             << regExp.match("hello");

    QRegularExpression reDate("^(\\d\\d)/(\\d\\d)/(\\d\\d\\d\\d)$");
    QRegularExpressionMatch match0 = reDate.match("01/10/1949");

    if (match0.hasMatch()) {
        QString strMatch = match0.captured(0);
        QString day = match0.captured(1);
        QString month = match0.captured(2);
        QString year = match0.captured(3);

        qDebug() << "捕获文本:"
                 << "strMatch: " << strMatch
                 << "day: " << day
                 << "month: " << month
                 << "year: " << year;
    }

    QString ss("Apr 01");
    QRegularExpressionMatch match2 = reDate.match(ss, 0,
                                    QRegularExpression::PartialPreferCompleteMatch);

    bool bHasMatched = match2.hasMatch();
    bool bPartial = match2.hasPartialMatch();

    qDebug() << bHasMatched << bPartial;





    return a.exec();
}
