#include "mysyntaxhighlighter.h"


MySyntaxHighlighter::MySyntaxHighlighter(QTextDocument *parent)
    :QSyntaxHighlighter(parent)
{

}

void MySyntaxHighlighter::highlightBlock(const QString &text)
{
    QTextCharFormat format; //字符格式
    format.setFontWeight(QFont::Bold);
    format.setBackground(Qt::red); //背景
    format.setForeground(Qt::green); //字体

    QString pattern = "\\bgood\\b"; //匹配单词边界
    QRegExp expression(pattern);
    int index = text.indexOf(expression);
    while(index >=0 )
    {
        int length = expression.matchedLength();
        setFormat(index, length, format);
        index = text.indexOf(expression, index + length);
    }
}
