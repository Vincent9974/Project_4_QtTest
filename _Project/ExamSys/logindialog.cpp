#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QIODevice>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->imgLabel->setScaledContents(true);
    this->resize(ui->imgLabel->width(),ui->imgLabel->height());
    this->setWindowTitle("驾校科目一考试登陆");
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    this->setFixedSize(width(),height());
}

LoginDialog::~LoginDialog()
{
    delete ui;
}


void LoginDialog::on_loginButtom_clicked()
{
    //测试槽功能
    //QMessageBox::information(this,"提示","槽方法调用!");

    //正则表达式验证邮箱地址 用户名@域名
    //^表示开始,$代表结束
    //+表示匹配次数>=1次,*表示匹配任意次数, {n,m}至少n次,至多m次

//    ^                      # 匹配字符串的开始
//    [A-Za-z0-9]+           # 匹配一个或多个字母或数字
//    ([_\.][A-Za-z0-9]+)*   # 匹配下划线(_)或点(.)紧跟着一个或多个字母或数字的模式，可以重复零次或多次
//    @                      # 匹配电子邮件地址中的@
//    ([A-Za-z0-9\-]+\.)+    # 匹配一个或多个由字母、数字或短横线(-)组成的子域名，紧跟着一个点(.)
//    [A-Za-z]{2,6}          # 匹配最后的顶级域名（TLD），如com、net等，要求为2到6个字母
//    $                      # 匹配字符串的结束

    QRegExp rx("^[A-Za-z0-9]+([_.][A-Za-z0-9]+)*@([A-Za-z0-9-]+.)+[A-Za-z]{2,6}$");
    bool res = rx.exactMatch(ui->accountEdit->text());

    if(!res)
    {
        QMessageBox::information(this,"提示","非法的邮箱地址,请重新输入:",QMessageBox::Ok);
        ui->accountEdit->clear();
        ui->passwordEdit->clear();
        ui->accountEdit->setFocus();
        return;
    }
//    else
//    {
//        QMessageBox::information(this,"提示","欢迎登陆科目一考试系统");
//    }


    else
    {
        QString strLine;
        QString strAcc;
        QString strPwd;

        QStringList strList;
        QString filename = "account.txt";

        QFile file(filename);

        strAcc = ui->accountEdit->text();
        strPwd = ui->passwordEdit->text();

        QTextStream stream(&file);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            while(!stream.atEnd())
            {
                strLine = stream.readLine();
                strList = strLine.split(",");
                if(strList[0] == strAcc)
                {
                    if(strList[1] == strPwd)
                    {
                        QMessageBox::information(this,"提示","欢迎进入考试系统");
                        file.close();
                        done(Accepted); //关闭对话框并返回accept的结果
                        return;
                    }
                    else
                    {
                        QMessageBox::information(this,"提示","密码错误");
                        ui->passwordEdit->clear();
                        ui->passwordEdit->setFocus();
                        file.close();
                        return;
                    }
                }
            }

            QMessageBox::information(this,"提示","没有此账号");
            ui->accountEdit->clear();
            ui->accountEdit->setFocus();
            file.close();
            return;

        }
        else
        {
            QMessageBox::information(this,"提示","读取保存的账号文件失败!",QMessageBox::Ok);
            return;
        }

    }


}

void LoginDialog::on_cancelButtom_clicked()
{
    done(Rejected);
}


