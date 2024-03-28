#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mysyntaxhighlighter.h"
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showTextFrame(); //遍历文档框架
    void showTextBlock(); //遍历文本块
    void showTextFont(bool checked); //设置文本字体

    void insertTable(); //插入表格
    void insertList(); //插入列表
    void insertImage(); //插入图片

    void textFind(); //查找文本
    void textNext(); //查找下一个


private:
    Ui::MainWindow *ui;
    MySyntaxHighlighter *m_sLighter;

    QLineEdit* m_lineEdit;
    QDialog *m_findDialog;

};
#endif // MAINWINDOW_H
