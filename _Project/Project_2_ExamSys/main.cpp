#include "logindialog.h"
#include "examdialog.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    //登陆函数
//    LoginDialog w;
//    w.show();

//    //考试用时
//    ExamDialog ed;
//    ed.show();


    LoginDialog logDialog;
    int res = logDialog.exec();

    if(res == QDialog::Accepted)
    {
        ExamDialog *examDiadlog;
        examDiadlog = new ExamDialog;
    }
    else{
        return 0;
    }

    return a.exec();
}
