#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "childwidow.h"
#include <QSignalMapper>
#include <QMdiSubWindow>
#include <QtPrintSupport/QPrinter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initMainWindow();
    void docNew();
    void docOpen();
    void docSave();
    void docSaveAs();

    void docPrint();
    void docPrintPreview();

    //文档操作
    void docUndo();
    void docRedo();
    void docCut();
    void docCopy();
    void docPaste();

    void textItalic();
    void textUnderline();
    void textBold();

    void textFamily(const QString &fmly);
    void textSize(const QString &ts);

    void textColor();
    void paraStyle(int nStyle);


private slots:
    void on_newAction_triggered();

    void refreshMenus();

    void addSubWnd();

    void on_closeAction_triggered();

    void on_closeAllAction_triggered();

    void on_titleAction_triggered();

    void on_cascadeAction_triggered();

    void on_nextAction_triggered();

    void on_previousAction_triggered();

    void on_aboutAction_triggered();

    void setActiveSubWindow(QWidget* wnd);

    void on_openAction_triggered();

    void on_saveAction_triggered();

    void on_saveAsAction_triggered();

    void on_uodoAction_triggered();

    void on_redoAction_triggered();

    void on_cutAction_triggered();

    void on_copyAction_triggered();

    void on_pasteAction_triggered();

    void on_action_B_3_triggered();

    void on_italicAction_triggered();

    void on_underlindeAction_triggered();

    void on_boldAction_triggered();

    void on_fontComboBox_activated(const QString &arg1);

    void on_sizeComboBox_activated(const QString &arg1);

    void on_leftAlignAction_triggered();

    void on_rightAlignAction_triggered();

    void on_centerAction_triggered();

    void on_justifyAction_triggered();

    void on_colorAction_triggered();

    void on_comboBox_activated(int index);

    void on_printAction_triggered();

    void printPreview(QPrinter* printer);

    void on_printPreviewAction_triggered();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    void formatEnabled();
    ChildWindow* activateChildWindow();
    QSignalMapper* m_WndMapper; //信号映射器
    QMdiSubWindow* findChildWnd(const QString& docName);

};
#endif // MAINWINDOW_H
