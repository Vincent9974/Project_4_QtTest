#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFrame>
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>


QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void createCtrlFrame(); // 创建控制框架
    void createContentFrame(); // 创建内容框架

    // 给组合框添加颜色列表
    void fillColorList(QComboBox* comboBox);


public slots:
    void showWindow(int index); // 显示窗口
    void showWindowText(int index); // 显示窗口文本
    void showButton(int index); // 显示按钮
    void showButtonText(int index); // 显示按钮文本
    void showBase(int index); // 显示基础

private:
    // 控制框架和内容框架
    QFrame *m_ctrlFrame;
    QFrame *m_contentFrame;

    // 窗口控件及其标签
    QLabel *m_windowLabel;
    QComboBox *m_windowComboBox;
    QLabel *m_windowTextLabel;
    QComboBox *m_windowTextComboBox;

    // 按钮控件及其标签
    QLabel *m_buttonLabel;
    QComboBox *m_buttonComboBox;
    QLabel *m_buttonTextLabel;
    QComboBox *m_buttonTextComboBox;

    // 基础控件及其标签
    QLabel *m_baseLabel;
    QComboBox *m_baseComboBox;

    // 内容控件
    QLabel *m_label1;
    QLabel *m_label2;
    QComboBox *m_comboBox1;
    QLineEdit *m_lineEdit;
    QTextEdit *m_textEdit;
    QPushButton *m_okBtn;
    QPushButton *m_cancelBtn;

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
