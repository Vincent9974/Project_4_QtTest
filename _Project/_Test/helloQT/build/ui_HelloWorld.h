/********************************************************************************
** Form generated from reading UI file 'HelloWorld.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELLOWORLD_H
#define UI_HELLOWORLD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HelloWorld
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HelloWorld)
    {
        if (HelloWorld->objectName().isEmpty())
            HelloWorld->setObjectName(QString::fromUtf8("HelloWorld"));
        HelloWorld->resize(802, 605);
        centralwidget = new QWidget(HelloWorld);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(290, 200, 75, 23));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(250, 160, 271, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe \345\256\213\344\275\223 Std L"));
        font.setPointSize(24);
        label->setFont(font);
        HelloWorld->setCentralWidget(centralwidget);
        menubar = new QMenuBar(HelloWorld);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 802, 22));
        HelloWorld->setMenuBar(menubar);
        statusbar = new QStatusBar(HelloWorld);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        HelloWorld->setStatusBar(statusbar);

        retranslateUi(HelloWorld);

        QMetaObject::connectSlotsByName(HelloWorld);
    } // setupUi

    void retranslateUi(QMainWindow *HelloWorld)
    {
        HelloWorld->setWindowTitle(QCoreApplication::translate("HelloWorld", "HelloWorld", nullptr));
        pushButton->setText(QCoreApplication::translate("HelloWorld", "OK", nullptr));
        label->setText(QCoreApplication::translate("HelloWorld", "HelloWorld", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HelloWorld: public Ui_HelloWorld {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELLOWORLD_H
