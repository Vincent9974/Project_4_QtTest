#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include "inputdlg.h"


class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void ShowFileDlg();
    void ShowColorDlg();
    void ShowFontDlg();
    void ShowInputDlg();




private:
    QPushButton* m_fileBtn; //打开文件对话框
    QLineEdit* m_fileLineEdit; //显示所选文件路径
    QPushButton* m_colorBtn; //打开颜色对话框
    QFrame* m_colorFrame; //显示所选颜色效果
    QPushButton* m_fontBtn; //打开字体对话框
    QLineEdit* m_fontLineEdit; //显示所选字体效果
    QPushButton* m_inputBtn; //显示输入对话框

    InputDlg* m_inputDlg;
    QPushButton* m_msgBtn;

    QGridLayout* m_mainLayout;


};
#endif // DIALOG_H
