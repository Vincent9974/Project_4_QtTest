#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <inputdlg.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    QPushButton* m_fileBtn;    //打开文件对话框
    QLineEdit* m_fileLineEdit; //显示所选文件路径
    QPushButton* m_colorBtn;   //打开颜色对话框
    QFrame* m_colorFrame; //显示所选颜色效果
    QPushButton* m_fontBtn; //打开字体对话框
    QLineEdit* m_fontLineEdit;

    QPushButton* m_inputBtn;
    InputDlg* m_inputDlg;


    QGridLayout* m_mainLayout; //布局管理器

private:
    Ui::Dialog *ui;


private slots:
    void ShowFileDialog();
    void ShowColorDlg();
    void ShowFontDialog();
    void ShowInputDialog();

};
#endif // DIALOG_H
