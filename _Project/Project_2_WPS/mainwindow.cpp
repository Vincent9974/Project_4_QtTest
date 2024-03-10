#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMdiSubWindow>
#include "childwidow.h"
#include <QCloseEvent>
#include <QFileDialog>
#include <Qstring>
#include <QColorDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initMainWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMainWindow()
{
    // 初始化字号列表
    QFontDatabase fontdb;
    foreach(int fontsize, fontdb.standardSizes())
        ui->sizeComboBox->addItem(QString::number(fontsize));

    QFont   defFont;
    QString sFontSize;
    int defFontSize;   //默认字号
    int defFontindex;  //默认索引号

    defFont = QApplication::font();
    defFontSize = defFont.pointSize();
    sFontSize = QString::number(defFontSize);

    defFontindex = ui->sizeComboBox->findText(sFontSize);
    ui->sizeComboBox->setCurrentIndex(defFontindex);

    // 拉大子窗口会出现滚动条
    ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    refreshMenus();
    connect(ui->mdiArea, &QMdiArea::subWindowActivated,
            this, &MainWindow::refreshMenus);

    addSubWnd();
    connect(ui->menu_W, &QMenu::aboutToShow,
            this,&MainWindow::addSubWnd);

    //创建信号映射器
    m_WndMapper =  new QSignalMapper(this);
    connect(m_WndMapper, SIGNAL(mapped(QWidget*)),
            this, SLOT(setActiveSubWindow(QWidget*)));

    QActionGroup *alignGroup = new QActionGroup(this);
    alignGroup->addAction(ui->leftAlignAction);
    alignGroup->addAction(ui->rightAlignAction);
    alignGroup->addAction(ui->centerAction);
    alignGroup->addAction(ui->justifyAction);
}

void MainWindow::docNew()
{
    ChildWindow *childwnd = new ChildWindow;
    ui->mdiArea->addSubWindow(childwnd);
    connect(childwnd, SIGNAL(copyAvailable(bool)),
            ui->cutAction,SLOT(setEnabled(bool)));
    connect(childwnd, SIGNAL(copyAvailable(bool)),
            ui->copyAction,SLOT(setEnabled(bool)));

    childwnd->newDoc();
    childwnd->show();

    formatEnabled();

}

void MainWindow::docOpen()
{
    QString docName = QFileDialog::getOpenFileName(this, QString("选择文件"), QString(""), QString("文本文件 (*.txt);;所有文件 (*.*)"));

    if(!docName.isEmpty())
    {
        QMdiSubWindow* existWnd = findChildWnd(docName);
        if(existWnd)
        {
            ui->mdiArea->setActiveSubWindow(existWnd);
            return;
        }

        ChildWindow* childWnd = new ChildWindow;
        ui->mdiArea->addSubWindow(childWnd);

        connect(childWnd,SIGNAL(copyAvailable(vool)),
                ui->cutAction, SLOT(setEnable(bool)));

        connect(childWnd,SIGNAL(copyAvailable(vool)),
                ui->copyAction, SLOT(setEnable(bool)));

        if(childWnd->loadDoc(docName))
        {
            statusBar()->showMessage("文档已打开",3000);
            childWnd->show();
            formatEnabled();
        }
        else
        {
            childWnd->close();
        }

    }
}

void MainWindow::docSave()
{
    if(activateChildWindow() && activateChildWindow() -> saveDoc())
        statusBar()->showMessage("保存成功", 3000);
}

void MainWindow::docSaveAs()
{
    if(activateChildWindow() && activateChildWindow()->saveAsDoc())
        statusBar() ->showMessage("保存成功",3000);
}

void MainWindow::docPrint()
{
    QPrinter pter(QPrinter::HighResolution);
    QPrintDialog* ddlg = new QPrintDialog(&pter,this);
    if(activateChildWindow())
        ddlg->setOption(QAbstractPrintDialog::PrintSelection, true);
    ddlg->setWindowTitle("打印文档");

    ChildWindow* ChildWindow = activateChildWindow();

    if(ddlg->exec() == QDialog::Accepted)
        ChildWindow->print(&pter);

    delete ddlg;
}

void MainWindow::docPrintPreview()
{
    QPrinter pter;
    QPrintPreviewDialog preview(&pter, this);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)),
            this, SLOT(printPreview(QPrinter*)));
    preview.exec();
}

void MainWindow::docUndo()
{
    if(activateChildWindow())
        activateChildWindow()->undo();
}

void MainWindow::docRedo()
{
    if(activateChildWindow())
        activateChildWindow()->redo();
}

void MainWindow::docCut()
{
    if(activateChildWindow())
        activateChildWindow()->cut();
}

void MainWindow::docCopy()
{
    if(activateChildWindow())
        activateChildWindow()->copy();
}

void MainWindow::docPaste()
{
    if(activateChildWindow())
        activateChildWindow()->paste();
}

void MainWindow::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(ui->italicAction->isChecked());


    if(activateChildWindow())
        activateChildWindow()->setFormatOnSelectedWord(fmt);
}

void MainWindow::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(ui->underlindeAction->isChecked());
    if(activateChildWindow())
        activateChildWindow()->setFormatOnSelectedWord(fmt);
}

void MainWindow::textBold()
{
    QTextCharFormat fmt;
    bool res = ui->boldAction->isChecked();
    fmt.setFontWeight(res ? QFont::Bold : QFont::Normal);
    if(activateChildWindow())
        activateChildWindow()->setFormatOnSelectedWord(fmt);
}

void MainWindow::textFamily(const QString &fmly)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(fmly);
    if(activateChildWindow())
        activateChildWindow()->setFormatOnSelectedWord(fmt);
}

void MainWindow::textSize(const QString &ts)
{
    qreal pointSize = ts.toFloat();
    if(ts.toFloat() > 0)
    {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        if(activateChildWindow())
            activateChildWindow()->setFormatOnSelectedWord(fmt);
    }

}

void MainWindow::textColor()
{
    if(activateChildWindow())
    {
        //获取用户选择的颜色
        QColor color = QColorDialog::getColor(activateChildWindow()->textColor(),
                                              this);
        if(!color.isValid()) return;

        QTextCharFormat fmt;
        fmt.setForeground(color);
        activateChildWindow()->setFormatOnSelectedWord(fmt);

        //更新工具栏颜色图标
        QPixmap pix(16,16);
        pix.fill(color);
        ui->colorAction->setIcon(pix);
    }
}

void MainWindow::paraStyle(int nStyle)
{
    if(activateChildWindow())
        activateChildWindow()->setParaStyle(nStyle);
}




void MainWindow::formatEnabled()
{
    ui->boldAction->setEnabled(true);
    ui->italicAction->setEnabled(true);
    ui->underlindeAction->setEnabled(true);
    ui->leftAlignAction->setEnabled(true);
    ui->centerAction->setEnabled(true);
    ui->rightAlignAction->setEnabled(true);
    ui->justifyAction->setEnabled(true);
    ui->colorAction->setEnabled(true);
}

ChildWindow *MainWindow::activateChildWindow()
{
    QMdiSubWindow* actWnd =  ui->mdiArea->activeSubWindow();
    if(actWnd)
    {
        return qobject_cast<ChildWindow* >(actWnd->widget());
    }
    else
        return 0;
}

QMdiSubWindow *MainWindow::findChildWnd(const QString &docName)
{
    QString strFile = QFileInfo(docName).canonicalPath();

    // 遍历当前所有子窗口
    foreach(QMdiSubWindow* subWnd, ui->mdiArea->subWindowList())
    {
        ChildWindow* childWnd = qobject_cast<ChildWindow*>(subWnd->widget());
        if(childWnd->m_CurDocPath == strFile) return subWnd;
    }
    return 0;
}

void MainWindow::refreshMenus()
{
    bool hasChild;
    hasChild = (activateChildWindow() != 0);

    ui->saveAction->setEnabled(hasChild);
    ui->saveAsAction->setEnabled(hasChild);
    ui->printPreviewAction->setEnabled(hasChild);
    ui->printAction->setEnabled(hasChild);
    ui->pasteAction->setEnabled(hasChild);
    ui->closeAction->setEnabled(hasChild);
    ui->closeAllAction->setEnabled(hasChild);
    ui->titleAction->setEnabled(hasChild);
    ui->cascadeAction->setEnabled(hasChild);
    ui->nextAction->setEnabled(hasChild);
    ui->previousAction->setEnabled(hasChild);

    // 文档打开且有内容选中
    bool hasSelect(activateChildWindow() &&
                   activateChildWindow()->textCursor().hasSelection());

    ui->cutAction->setEnabled(hasSelect);
    ui->copyAction->setEnabled(hasSelect);
    ui->boldAction->setEnabled(hasSelect);
    ui->italicAction->setEnabled(hasSelect);
    ui->underlindeAction->setEnabled(hasSelect);
    ui->leftAlignAction->setEnabled(hasSelect);
    ui->centerAction->setEnabled(hasSelect);
    ui->rightAlignAction->setEnabled(hasSelect);
    ui->justifyAction->setEnabled(hasSelect);
    ui->colorAction->setEnabled(hasSelect);

}

void MainWindow::addSubWnd()
{
    ui->menu_W->clear();
    ui->menu_W->addAction(ui->closeAction);
    ui->menu_W->addAction(ui->closeAllAction);
    ui->menu_W->addSeparator();
    ui->menu_W->addAction(ui->titleAction);
    ui->menu_W->addAction(ui->cascadeAction);
    ui->menu_W->addSeparator();
    ui->menu_W->addAction(ui->nextAction);
    ui->menu_W->addAction(ui->previousAction);

    QList<QMdiSubWindow*> wnds = ui->mdiArea->subWindowList();
    if(!wnds.isEmpty())
    {
        ui->menu_W->addSeparator();
    }

    for(int i=0; i < wnds.size(); ++i)
    {
        ChildWindow* childWnd = qobject_cast<ChildWindow*> (wnds.at(i)->widget());

        QString menuitem_text;
        menuitem_text = QString("%1 %2")
                .arg(i + 1)
                .arg(childWnd->getCurDocName());

        QAction *menuitem_act = ui->menu_W->addAction(menuitem_text);
        menuitem_act->setCheckable(true);
        menuitem_act->setChecked(childWnd == activateChildWindow());

        connect(menuitem_act, SIGNAL(triggered(bool)),
                m_WndMapper,  SLOT(map()));
        m_WndMapper->setMapping(menuitem_act, wnds.at(i));
    }
}


void MainWindow::on_newAction_triggered()
{
    docNew();
}

void MainWindow::on_closeAction_triggered()
{
    ui->mdiArea->closeActiveSubWindow();
}

void MainWindow::on_closeAllAction_triggered()
{
    ui->mdiArea->closeAllSubWindows();
}

void MainWindow::on_titleAction_triggered()
{
    ui->mdiArea->tileSubWindows();
}

void MainWindow::on_cascadeAction_triggered()
{
    ui->mdiArea->cascadeSubWindows();
}


void MainWindow::on_nextAction_triggered()
{
    ui->mdiArea->activateNextSubWindow();
}


void MainWindow::on_previousAction_triggered()
{
    ui->mdiArea->activatePreviousSubWindow();
}

void MainWindow::setActiveSubWindow(QWidget *wnd)
{
    if(!wnd) return;
    ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow*>(wnd));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    ui->mdiArea->closeAllSubWindows();
    if(ui->mdiArea->currentSubWindow())
    {
        event->ignore();
    }
    else
    {
        event->accept();
    }
}



void MainWindow::on_openAction_triggered()
{
    docOpen();
}

void MainWindow::on_aboutAction_triggered()
{

}

void MainWindow::on_saveAction_triggered()
{
    docSave();
}

void MainWindow::on_saveAsAction_triggered()
{
    docSaveAs();
}

void MainWindow::on_uodoAction_triggered()
{
    docUndo();
}

void MainWindow::on_redoAction_triggered()
{
    docRedo();
}

void MainWindow::on_cutAction_triggered()
{
    docCut();
}

void MainWindow::on_copyAction_triggered()
{
    docCopy();
}

void MainWindow::on_pasteAction_triggered()
{
    docPaste();
}

void MainWindow::on_action_B_3_triggered()
{
    textBold();
}

void MainWindow::on_italicAction_triggered()
{
    textItalic();
}

void MainWindow::on_underlindeAction_triggered()
{
    textUnderline();
}

void MainWindow::on_boldAction_triggered()
{
    textBold();
}

void MainWindow::on_fontComboBox_activated(const QString &arg1)
{
    textFamily(arg1);
}

void MainWindow::on_sizeComboBox_activated(const QString &arg1)
{
    textSize(arg1);
}

void MainWindow::on_leftAlignAction_triggered()
{
    if(activateChildWindow())
        activateChildWindow()->setAlignOfDocumentText(1);
}

void MainWindow::on_rightAlignAction_triggered()
{
    if(activateChildWindow())
        activateChildWindow()->setAlignOfDocumentText(2);
}

void MainWindow::on_centerAction_triggered()
{
    if(activateChildWindow())
        activateChildWindow()->setAlignOfDocumentText(3);
}

void MainWindow::on_justifyAction_triggered()
{
    if(activateChildWindow())
        activateChildWindow()->setAlignOfDocumentText(4);
}

void MainWindow::on_colorAction_triggered()
{
    textColor();
}

void MainWindow::on_comboBox_activated(int index)
{
    paraStyle(index);
}

void MainWindow::on_printAction_triggered()
{
    docPrint();
}

void MainWindow::printPreview(QPrinter *printer)
{
    activateChildWindow()->print(printer);
}



void MainWindow::on_printPreviewAction_triggered()
{
    docPrintPreview();
}
