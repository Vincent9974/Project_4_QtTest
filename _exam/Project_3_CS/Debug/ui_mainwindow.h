/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad;
    QAction *actionSave;
    QAction *actionconfig1;
    QAction *actionconfig2;
    QAction *actionconfig3;
    QWidget *centralWidget;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditAccount;
    QLineEdit *lineEditPassword;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAdmin;
    QMenu *menuAbout;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QLatin1String("QMainWindow\n"
"{\n"
"	\n"
"}"));
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionconfig1 = new QAction(MainWindow);
        actionconfig1->setObjectName(QStringLiteral("actionconfig1"));
        actionconfig1->setCheckable(true);
        actionconfig1->setEnabled(true);
        actionconfig2 = new QAction(MainWindow);
        actionconfig2->setObjectName(QStringLiteral("actionconfig2"));
        actionconfig2->setCheckable(true);
        actionconfig3 = new QAction(MainWindow);
        actionconfig3->setObjectName(QStringLiteral("actionconfig3"));
        actionconfig3->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 134, 71, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(14);
        label_2->setFont(font);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(60, 75, 71, 51));
        label_3->setFont(font);
        lineEditAccount = new QLineEdit(centralWidget);
        lineEditAccount->setObjectName(QStringLiteral("lineEditAccount"));
        lineEditAccount->setGeometry(QRect(130, 90, 191, 20));
        lineEditPassword = new QLineEdit(centralWidget);
        lineEditPassword->setObjectName(QStringLiteral("lineEditPassword"));
        lineEditPassword->setGeometry(QRect(130, 150, 191, 20));
        lineEditPassword->setEchoMode(QLineEdit::Password);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuAdmin = new QMenu(menuBar);
        menuAdmin->setObjectName(QStringLiteral("menuAdmin"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuAdmin->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionSave);
        menuAdmin->addAction(actionconfig1);
        menuAdmin->addAction(actionconfig2);
        menuAdmin->addAction(actionconfig3);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionLoad->setText(QApplication::translate("MainWindow", "Load", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        actionLoad->setStatusTip(QApplication::translate("MainWindow", "\344\273\216\346\234\215\345\212\241\345\231\250\344\270\255\357\274\214\346\212\212\346\234\254\350\264\246\345\217\267\347\232\204\351\205\215\347\275\256\351\203\275\344\270\213\350\275\275\345\210\260\346\234\254\345\234\260\357\274\214\345\271\266\346\233\264\346\226\260\345\210\260\350\275\257\344\273\266\347\225\214\351\235\242\347\232\204\346\230\276\347\244\272\344\270\255", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        actionSave->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        actionconfig1->setText(QApplication::translate("MainWindow", "config1", Q_NULLPTR));
        actionconfig2->setText(QApplication::translate("MainWindow", "config2", Q_NULLPTR));
        actionconfig3->setText(QApplication::translate("MainWindow", "config3", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\350\264\246\346\210\267\357\274\232", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "Config", Q_NULLPTR));
        menuAdmin->setTitle(QApplication::translate("MainWindow", "Admin", Q_NULLPTR));
        menuAbout->setTitle(QApplication::translate("MainWindow", "About", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
