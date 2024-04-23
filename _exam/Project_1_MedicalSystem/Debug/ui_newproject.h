/********************************************************************************
** Form generated from reading UI file 'newproject.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPROJECT_H
#define UI_NEWPROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newProject
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QLabel *label_2;
    QLineEdit *lineEditProjectName;
    QLineEdit *lineEditFilePath;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *comboBox;
    QLineEdit *lineEditWidth;
    QLineEdit *lineEditHeight;
    QLabel *label_7;
    QLineEdit *lineEdit_3;
    QLabel *label_8;
    QLineEdit *lineEditSelectModel;
    QToolButton *toolButtonModel;
    QToolButton *toolButtonFIlePath;
    QPushButton *pushButton;
    QPushButton *pushButtonEnter;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *newProject)
    {
        if (newProject->objectName().isEmpty())
            newProject->setObjectName(QStringLiteral("newProject"));
        newProject->resize(800, 600);
        centralwidget = new QWidget(newProject);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 40, 54, 12));
        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(50, 80, 91, 18));
        radioButton_2 = new QRadioButton(centralwidget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(150, 80, 91, 18));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 170, 54, 12));
        lineEditProjectName = new QLineEdit(centralwidget);
        lineEditProjectName->setObjectName(QStringLiteral("lineEditProjectName"));
        lineEditProjectName->setGeometry(QRect(50, 200, 471, 31));
        lineEditFilePath = new QLineEdit(centralwidget);
        lineEditFilePath->setObjectName(QStringLiteral("lineEditFilePath"));
        lineEditFilePath->setGeometry(QRect(50, 290, 411, 31));
        lineEditFilePath->setReadOnly(true);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 260, 54, 12));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(50, 340, 54, 20));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(260, 350, 54, 20));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(490, 350, 54, 20));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(40, 370, 151, 41));
        lineEditWidth = new QLineEdit(centralwidget);
        lineEditWidth->setObjectName(QStringLiteral("lineEditWidth"));
        lineEditWidth->setGeometry(QRect(210, 380, 161, 31));
        lineEditWidth->setReadOnly(false);
        lineEditHeight = new QLineEdit(centralwidget);
        lineEditHeight->setObjectName(QStringLiteral("lineEditHeight"));
        lineEditHeight->setGeometry(QRect(430, 380, 161, 31));
        lineEditHeight->setReadOnly(false);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(50, 430, 54, 20));
        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(40, 470, 471, 31));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(50, 110, 54, 12));
        lineEditSelectModel = new QLineEdit(centralwidget);
        lineEditSelectModel->setObjectName(QStringLiteral("lineEditSelectModel"));
        lineEditSelectModel->setGeometry(QRect(50, 130, 471, 31));
        lineEditSelectModel->setReadOnly(true);
        toolButtonModel = new QToolButton(centralwidget);
        toolButtonModel->setObjectName(QStringLiteral("toolButtonModel"));
        toolButtonModel->setGeometry(QRect(550, 140, 38, 19));
        toolButtonFIlePath = new QToolButton(centralwidget);
        toolButtonFIlePath->setObjectName(QStringLiteral("toolButtonFIlePath"));
        toolButtonFIlePath->setGeometry(QRect(550, 300, 38, 19));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(590, 510, 80, 41));
        pushButtonEnter = new QPushButton(centralwidget);
        pushButtonEnter->setObjectName(QStringLiteral("pushButtonEnter"));
        pushButtonEnter->setGeometry(QRect(680, 510, 80, 41));
        newProject->setCentralWidget(centralwidget);
        menubar = new QMenuBar(newProject);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        newProject->setMenuBar(menubar);
        statusbar = new QStatusBar(newProject);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        newProject->setStatusBar(statusbar);

        retranslateUi(newProject);

        QMetaObject::connectSlotsByName(newProject);
    } // setupUi

    void retranslateUi(QMainWindow *newProject)
    {
        newProject->setWindowTitle(QApplication::translate("newProject", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("newProject", "\345\267\245\347\250\213\347\261\273\345\236\213", Q_NULLPTR));
        radioButton->setText(QApplication::translate("newProject", "\346\226\260\345\273\272\345\267\245\347\250\213", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("newProject", "\346\250\241\346\235\277\345\267\245\347\250\213", Q_NULLPTR));
        label_2->setText(QApplication::translate("newProject", "\345\267\245\347\250\213\345\220\215\347\247\260", Q_NULLPTR));
        label_3->setText(QApplication::translate("newProject", "\345\267\245\347\250\213\350\267\257\345\276\204", Q_NULLPTR));
        label_4->setText(QApplication::translate("newProject", "\345\210\206\350\276\250\347\216\207", Q_NULLPTR));
        label_5->setText(QApplication::translate("newProject", "\345\256\275\345\272\246(W)", Q_NULLPTR));
        label_6->setText(QApplication::translate("newProject", "\345\256\275\345\272\246(H)", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("newProject", "\350\207\252\345\256\232\344\271\211\345\210\206\350\276\250\347\216\207", Q_NULLPTR)
         << QApplication::translate("newProject", "\346\226\260\345\273\272\351\241\271\347\233\256", Q_NULLPTR)
        );
        label_7->setText(QApplication::translate("newProject", "\345\267\245\347\250\213\346\217\217\350\277\260", Q_NULLPTR));
        label_8->setText(QApplication::translate("newProject", "\351\200\211\346\213\251\346\250\241\346\235\277", Q_NULLPTR));
        toolButtonModel->setText(QApplication::translate("newProject", "...", Q_NULLPTR));
        toolButtonFIlePath->setText(QApplication::translate("newProject", "...", Q_NULLPTR));
        pushButton->setText(QApplication::translate("newProject", "\345\217\226\346\266\210", Q_NULLPTR));
        pushButtonEnter->setText(QApplication::translate("newProject", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class newProject: public Ui_newProject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPROJECT_H
