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
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionLoad;
    QAction *actionExport;
    QAction *actionSave;
    QAction *actionLatestUse;
    QAction *actionExit;
    QAction *actionLargestView;
    QAction *actionBigView;
    QAction *actionSmallView;
    QAction *actionListView;
    QAction *actionDetailedView;
    QAction *actionRun;
    QAction *actionDeplovement;
    QAction *actionRemake;
    QAction *actionPackUp;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuProject;
    QMenu *menuView;
    QMenu *menuHelp;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1800, 800);
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/iconWindow.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/iconNew.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon1);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/res/iconOpen.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon2);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionExport = new QAction(MainWindow);
        actionExport->setObjectName(QStringLiteral("actionExport"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionLatestUse = new QAction(MainWindow);
        actionLatestUse->setObjectName(QStringLiteral("actionLatestUse"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/res/EXIT.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon3);
        actionLargestView = new QAction(MainWindow);
        actionLargestView->setObjectName(QStringLiteral("actionLargestView"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/res/other.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionLargestView->setIcon(icon4);
        actionBigView = new QAction(MainWindow);
        actionBigView->setObjectName(QStringLiteral("actionBigView"));
        actionBigView->setIcon(icon4);
        actionSmallView = new QAction(MainWindow);
        actionSmallView->setObjectName(QStringLiteral("actionSmallView"));
        actionSmallView->setIcon(icon4);
        actionListView = new QAction(MainWindow);
        actionListView->setObjectName(QStringLiteral("actionListView"));
        actionDetailedView = new QAction(MainWindow);
        actionDetailedView->setObjectName(QStringLiteral("actionDetailedView"));
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QStringLiteral("actionRun"));
        actionDeplovement = new QAction(MainWindow);
        actionDeplovement->setObjectName(QStringLiteral("actionDeplovement"));
        actionRemake = new QAction(MainWindow);
        actionRemake->setObjectName(QStringLiteral("actionRemake"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/res/remake.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionRemake->setIcon(icon5);
        actionPackUp = new QAction(MainWindow);
        actionPackUp->setObjectName(QStringLiteral("actionPackUp"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/res/packUp.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionPackUp->setIcon(icon6);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1800, 21));
        menuProject = new QMenu(menuBar);
        menuProject->setObjectName(QStringLiteral("menuProject"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuProject->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuProject->addAction(actionNew);
        menuProject->addAction(actionOpen);
        menuProject->addAction(actionClose);
        menuProject->addSeparator();
        menuProject->addAction(actionLoad);
        menuProject->addAction(actionExport);
        menuProject->addAction(actionSave);
        menuProject->addAction(actionLatestUse);
        menuProject->addSeparator();
        menuProject->addAction(actionExit);
        menuView->addAction(actionLargestView);
        menuView->addAction(actionBigView);
        menuView->addAction(actionSmallView);
        menuView->addSeparator();
        menuView->addAction(actionListView);
        menuView->addAction(actionDetailedView);
        menuHelp->addAction(actionRun);
        menuHelp->addAction(actionDeplovement);
        menuHelp->addAction(actionRemake);
        menuHelp->addAction(actionPackUp);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionOpen);
        toolBar->addSeparator();
        toolBar->addAction(actionExit);
        toolBar->addAction(actionRemake);
        toolBar->addAction(actionPackUp);
        toolBar->addSeparator();
        toolBar->addAction(actionLargestView);
        toolBar->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionNew->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\267\245\347\250\213", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionOpen->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\345\267\245\347\250\213", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionClose->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\345\267\245\347\250\213", Q_NULLPTR));
        actionLoad->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245", Q_NULLPTR));
        actionExport->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionLatestUse->setText(QApplication::translate("MainWindow", "\346\234\200\350\277\221\344\275\277\347\224\250\346\226\207\344\273\266", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", Q_NULLPTR));
        actionLargestView->setText(QApplication::translate("MainWindow", "\346\234\200\345\244\247", Q_NULLPTR));
        actionBigView->setText(QApplication::translate("MainWindow", "\345\244\247\345\233\276", Q_NULLPTR));
        actionSmallView->setText(QApplication::translate("MainWindow", "\345\260\217\345\233\276", Q_NULLPTR));
        actionListView->setText(QApplication::translate("MainWindow", "\345\210\227\350\241\250", Q_NULLPTR));
        actionDetailedView->setText(QApplication::translate("MainWindow", "\350\257\246\347\273\206", Q_NULLPTR));
        actionRun->setText(QApplication::translate("MainWindow", "\350\277\220\350\241\214", Q_NULLPTR));
        actionDeplovement->setText(QApplication::translate("MainWindow", "\345\274\200\345\217\221", Q_NULLPTR));
        actionRemake->setText(QApplication::translate("MainWindow", "\346\201\242\345\244\215", Q_NULLPTR));
        actionPackUp->setText(QApplication::translate("MainWindow", "\346\211\223\345\214\205", Q_NULLPTR));
        menuProject->setTitle(QApplication::translate("MainWindow", "\345\267\245\347\250\213", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("MainWindow", "\350\247\206\345\233\276", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
