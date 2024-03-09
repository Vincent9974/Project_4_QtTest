#include "childwidow.h"
#include <QFileInfo>
#include <QByteArray>
#include <QFileDialog>
#include <QTextDocumentWriter>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTextBlockFormat>
#include <QTextListFormat>
#include <QtWidgets>

ChildWindow::ChildWindow()
{
    //子窗口关闭时销毁该类的实例对象

    setAttribute(Qt::WA_DeleteOnClose);

    m_bSaved = false;

}

void ChildWindow::newDoc()
{
    static int wndSeqNum = 1; //当前文档的序号
    m_CurDocPath = QString("WPS 文档 %1").arg(wndSeqNum++);

    //设置窗体标题, 文档改动后名称加"*"标识
    setWindowTitle(m_CurDocPath + "[*]" + "MyWPS");
    connect(document(), SIGNAL(contentsChanged()),
            this, SLOT(docBeModified()));
}

QString ChildWindow::getCurDocName()
{
    return QFileInfo(m_CurDocPath).fileName();
}

bool ChildWindow::loadDoc(const QString &docName)
{
    if(!docName.isEmpty())
    {
        QFile file(docName);
        if(!file.exists()) return false;
        if(!file.open(QFile::ReadOnly)) return false;

        QByteArray text = file.readAll();
        if(Qt::mightBeRichText(text))
        {
            setHtml(text);
        }
        else
        {
            setPlainText(text);
        }

        setCurDoc(docName);
        connect(document(),SIGNAL(contentsChanged()),
                this, SLOT(docBeModified()));
        return true;
    }
}

void ChildWindow::setCurDoc(const QString &docName)
{
    m_CurDocPath = QFileInfo(docName).canonicalPath();
    m_bSaved = true;
    document()->setModified(false); //文档未改动
    setWindowModified(false);
    setWindowTitle(getCurDocName() + "[*]");
}

bool ChildWindow::saveDoc()
{
    if(m_bSaved) return saveDocOpt(m_CurDocPath);
    else saveAsDoc();
}

bool ChildWindow::saveAsDoc()
{
    QString docName = QFileDialog::getSaveFileName(this,
                                 "另存为",
                                 m_CurDocPath,
                                 "HTML文档 (*.htm *.html);;"
                                 "所有文件(*.*)");
    if(docName.isEmpty()) return false;
    else return saveDocOpt(docName);
}

bool ChildWindow::saveDocOpt(QString docName)
{
    if(!(docName.endsWith(".html",Qt::CaseInsensitive))
            || docName.endsWith(".html",Qt::CaseInsensitive))
    {
        docName += ".html";
    }

    QTextDocumentWriter writer(docName);
    bool isSuccess = writer.write(this->document());
    if(isSuccess) setCurDoc(docName);
    return isSuccess;
}

void ChildWindow::setFormatOnSelectedWord(const QTextCharFormat& fmt)
{
    QTextCursor tcursor = textCursor();
    if(!tcursor.hasSelection()) tcursor.select(QTextCursor::WordUnderCursor);

    tcursor.mergeCharFormat(fmt);
    mergeCurrentCharFormat(fmt);
}

void ChildWindow::setAlignOfDocumentText(int aligntype)
{
    if(aligntype == 1)
        setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if(aligntype == 2)
        setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if(aligntype == 3)
        setAlignment(Qt::AlignCenter);
    else if(aligntype == 4)
        setAlignment(Qt::AlignJustify);
}

void ChildWindow::setParaStyle(int pStyle)
{
    QTextCursor tcursor = textCursor();
    QTextListFormat::Style sname;
    if(pStyle !=0)
    {
        switch(pStyle)
        {
            case 1:
                sname = QTextListFormat::ListDisc;
                break;
            case 2:
                sname = QTextListFormat::ListCircle;
                break;
            case 3:
                sname = QTextListFormat::ListSquare;
                break;
            case 4:
                sname = QTextListFormat::ListDecimal;
                break;
            case 5:
                sname = QTextListFormat::ListLowerAlpha;
                break;
            case 6:
                sname = QTextListFormat::ListUpperAlpha;
                break;
            case 7:
                sname = QTextListFormat::ListLowerRoman;
                break;
            case 8:
                sname = QTextListFormat::ListUpperRoman;
                break;
            default:
                sname = QTextListFormat::ListDisc;
        }

        tcursor.beginEditBlock();
        QTextBlockFormat tBlockFmt = tcursor.blockFormat(); //文本块格式
        QTextListFormat tListFmt;
        if(tcursor.currentList())
        {
            tcursor.currentList()->format();
        }
        else
        {
            tListFmt.setIndent(tBlockFmt.indent() + 1);
            tBlockFmt.setIndent(0);
            tcursor.setBlockFormat(tBlockFmt);
        }

        tListFmt.setStyle(sname);
        tcursor.createList(tListFmt);
        tcursor.endEditBlock();
    }
    else
    {
        QTextBlockFormat tbfmt;
        tbfmt.setObjectIndex(-1);
        tcursor.mergeBlockFormat(tbfmt);
    }
}

void ChildWindow::closeEvent(QCloseEvent *event)
{
    if(promptSave())
        event->accept();
    else
        event->ignore();

}

bool ChildWindow::promptSave()
{
    if(!document()->isModified()) return true;

    QMessageBox::StandardButton result;
    result = QMessageBox::warning(this,
                                  QString("系统提示"),
                                  QString("文档%1已修改,是否修改?")
                                  .arg(getCurDocName()),
                                  QMessageBox::Yes |
                                  QMessageBox::Discard |
                                  QMessageBox::No);
    if(result == QMessageBox::Yes)
        return saveDoc();
    else if(result == QMessageBox::No)
        return false;
    return true;
}

void ChildWindow::docBeModified()
{
    setWindowModified(document()->isModified());
}
