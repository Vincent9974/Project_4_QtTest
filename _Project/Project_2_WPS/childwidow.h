#ifndef CHILDWIND_H
#define CHILDWIND_H

#include <QTextEdit>

class ChildWindow : public QTextEdit
{
        Q_OBJECT
public:
    ChildWindow();
    QString m_CurDocPath; //当前文档路径
    void newDoc(); //新建文档
    QString getCurDocName(); //文档路径中提取文档名
    bool loadDoc(const QString& docName);
    void setCurDoc(const QString& docName);

    //保存文档
    bool saveDoc();
    bool saveAsDoc();
    bool saveDocOpt(QString docName);

    void setFormat();

    // 设置文字
    void setFormatOnSelectedWord(const QTextCharFormat & fmt);
    void setAlignOfDocumentText(int aligntype);

    void setParaStyle(int pStyle);

protected:
    void closeEvent(QCloseEvent *event);
private:
    bool promptSave();

private slots:
    void docBeModified(); //文档修改时,窗口的标题栏加'*'
private:
    bool m_bSaved; //文档是否保存

};

#endif // CHILDWIND_H
