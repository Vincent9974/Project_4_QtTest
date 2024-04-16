/********************************************************************************
** Form generated from reading UI file 'server.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Server
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit1;
    QLineEdit *lineEdit2;
    QLabel *label;
    QLabel *label_2;
    QLabel *labelJson;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Server)
    {
        if (Server->objectName().isEmpty())
            Server->setObjectName(QStringLiteral("Server"));
        Server->resize(405, 309);
        centralwidget = new QWidget(Server);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        lineEdit1 = new QLineEdit(centralwidget);
        lineEdit1->setObjectName(QStringLiteral("lineEdit1"));
        lineEdit1->setGeometry(QRect(130, 80, 113, 20));
        lineEdit2 = new QLineEdit(centralwidget);
        lineEdit2->setObjectName(QStringLiteral("lineEdit2"));
        lineEdit2->setGeometry(QRect(130, 140, 113, 20));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 80, 61, 21));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 140, 61, 21));
        labelJson = new QLabel(centralwidget);
        labelJson->setObjectName(QStringLiteral("labelJson"));
        labelJson->setGeometry(QRect(50, 210, 291, 51));
        Server->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Server);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 405, 21));
        Server->setMenuBar(menubar);
        statusbar = new QStatusBar(Server);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Server->setStatusBar(statusbar);

        retranslateUi(Server);

        QMetaObject::connectSlotsByName(Server);
    } // setupUi

    void retranslateUi(QMainWindow *Server)
    {
        Server->setWindowTitle(QApplication::translate("Server", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("Server", "key1", Q_NULLPTR));
        label_2->setText(QApplication::translate("Server", "key1", Q_NULLPTR));
        labelJson->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Server: public Ui_Server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
