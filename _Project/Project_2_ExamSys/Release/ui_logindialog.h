/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *imgLabel;
    QPushButton *loginButtom;
    QPushButton *cancelButtom;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *accountEdit;
    QLineEdit *passwordEdit;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(585, 388);
        imgLabel = new QLabel(LoginDialog);
        imgLabel->setObjectName(QString::fromUtf8("imgLabel"));
        imgLabel->setGeometry(QRect(0, 0, 591, 381));
        imgLabel->setPixmap(QPixmap(QString::fromUtf8(":/login.png")));
        loginButtom = new QPushButton(LoginDialog);
        loginButtom->setObjectName(QString::fromUtf8("loginButtom"));
        loginButtom->setGeometry(QRect(150, 289, 91, 31));
        QFont font;
        font.setPointSize(12);
        loginButtom->setFont(font);
        cancelButtom = new QPushButton(LoginDialog);
        cancelButtom->setObjectName(QString::fromUtf8("cancelButtom"));
        cancelButtom->setGeometry(QRect(419, 289, 81, 31));
        cancelButtom->setFont(font);
        label_2 = new QLabel(LoginDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(200, 180, 61, 21));
        QFont font1;
        font1.setPointSize(15);
        label_2->setFont(font1);
        label_3 = new QLabel(LoginDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(200, 230, 61, 21));
        label_3->setFont(font1);
        accountEdit = new QLineEdit(LoginDialog);
        accountEdit->setObjectName(QString::fromUtf8("accountEdit"));
        accountEdit->setGeometry(QRect(260, 180, 171, 20));
        passwordEdit = new QLineEdit(LoginDialog);
        passwordEdit->setObjectName(QString::fromUtf8("passwordEdit"));
        passwordEdit->setGeometry(QRect(260, 230, 171, 20));
        passwordEdit->setEchoMode(QLineEdit::Password);

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "LoginDialog", nullptr));
        imgLabel->setText(QString());
        loginButtom->setText(QCoreApplication::translate("LoginDialog", "\347\231\273\351\231\206", nullptr));
        cancelButtom->setText(QCoreApplication::translate("LoginDialog", "\345\217\226\346\266\210", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "\350\264\246\345\217\267", nullptr));
        label_3->setText(QCoreApplication::translate("LoginDialog", "\345\257\206\347\240\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
