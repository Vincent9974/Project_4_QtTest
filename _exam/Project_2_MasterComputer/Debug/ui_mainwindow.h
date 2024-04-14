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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_bg;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *labelx;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_temp;
    QLabel *label_fuel1;
    QLabel *label_fuel2;
    QLabel *label_fuel3;
    QLabel *label_RPM_main;
    QLabel *label_RPM_sub;
    QLabel *label_tank1;
    QLabel *label_tank2;
    QLabel *label_tank3;
    QLabel *label_tank4;
    QLabel *label_tank5;
    QLabel *label_arm;
    QProgressBar *progressBar_tank1;
    QProgressBar *progressBar_tank2;
    QProgressBar *progressBar_tank3;
    QProgressBar *progressBar_tank4;
    QProgressBar *progressBar_tank5;
    QProgressBar *progressBar_arm;
    QLabel *label_time;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1200, 864);
        MainWindow->setStyleSheet(QLatin1String("QProgressBar{\n"
"Border:0.1px solid gray;\n"
"background-color = rgb(74,75,83);\n"
"				}\n"
"QProgressBar:chunk{\n"
"	background-color = rgb(0,185,84);\n"
"}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_bg = new QLabel(centralWidget);
        label_bg->setObjectName(QStringLiteral("label_bg"));
        label_bg->setGeometry(QRect(0, 0, 1200, 864));
        label_bg->setPixmap(QPixmap(QString::fromUtf8(":/res/bg3.png")));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 240, 71, 16));
        label->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label->setTextFormat(Qt::AutoText);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(409, 240, 71, 16));
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_2->setTextFormat(Qt::AutoText);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(727, 240, 71, 16));
        label_3->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_3->setTextFormat(Qt::AutoText);
        labelx = new QLabel(centralWidget);
        labelx->setObjectName(QStringLiteral("labelx"));
        labelx->setGeometry(QRect(1040, 240, 71, 16));
        labelx->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        labelx->setTextFormat(Qt::AutoText);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(90, 330, 71, 16));
        label_5->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_5->setTextFormat(Qt::AutoText);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(89, 420, 71, 16));
        label_6->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_6->setTextFormat(Qt::AutoText);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(90, 510, 71, 16));
        label_7->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_7->setTextFormat(Qt::AutoText);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(89, 590, 71, 16));
        label_8->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_8->setTextFormat(Qt::AutoText);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(87, 680, 71, 16));
        label_9->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_9->setTextFormat(Qt::AutoText);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(70, 770, 111, 16));
        label_10->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_10->setTextFormat(Qt::AutoText);
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(390, 770, 111, 16));
        label_11->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_11->setTextFormat(Qt::AutoText);
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(700, 770, 111, 16));
        label_12->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_12->setTextFormat(Qt::AutoText);
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(1018, 350, 131, 20));
        label_13->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_13->setTextFormat(Qt::AutoText);
        label_temp = new QLabel(centralWidget);
        label_temp->setObjectName(QStringLiteral("label_temp"));
        label_temp->setGeometry(QRect(100, 270, 31, 16));
        label_temp->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_temp->setTextFormat(Qt::AutoText);
        label_fuel1 = new QLabel(centralWidget);
        label_fuel1->setObjectName(QStringLiteral("label_fuel1"));
        label_fuel1->setGeometry(QRect(100, 800, 31, 16));
        label_fuel1->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_fuel1->setTextFormat(Qt::AutoText);
        label_fuel2 = new QLabel(centralWidget);
        label_fuel2->setObjectName(QStringLiteral("label_fuel2"));
        label_fuel2->setGeometry(QRect(430, 800, 31, 16));
        label_fuel2->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_fuel2->setTextFormat(Qt::AutoText);
        label_fuel3 = new QLabel(centralWidget);
        label_fuel3->setObjectName(QStringLiteral("label_fuel3"));
        label_fuel3->setGeometry(QRect(740, 800, 31, 16));
        label_fuel3->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_fuel3->setTextFormat(Qt::AutoText);
        label_RPM_main = new QLabel(centralWidget);
        label_RPM_main->setObjectName(QStringLiteral("label_RPM_main"));
        label_RPM_main->setGeometry(QRect(410, 270, 31, 16));
        label_RPM_main->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_RPM_main->setTextFormat(Qt::AutoText);
        label_RPM_sub = new QLabel(centralWidget);
        label_RPM_sub->setObjectName(QStringLiteral("label_RPM_sub"));
        label_RPM_sub->setGeometry(QRect(730, 270, 31, 16));
        label_RPM_sub->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_RPM_sub->setTextFormat(Qt::AutoText);
        label_tank1 = new QLabel(centralWidget);
        label_tank1->setObjectName(QStringLiteral("label_tank1"));
        label_tank1->setGeometry(QRect(170, 330, 61, 16));
        label_tank1->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_tank1->setTextFormat(Qt::AutoText);
        label_tank2 = new QLabel(centralWidget);
        label_tank2->setObjectName(QStringLiteral("label_tank2"));
        label_tank2->setGeometry(QRect(170, 420, 61, 16));
        label_tank2->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_tank2->setTextFormat(Qt::AutoText);
        label_tank3 = new QLabel(centralWidget);
        label_tank3->setObjectName(QStringLiteral("label_tank3"));
        label_tank3->setGeometry(QRect(170, 510, 61, 16));
        label_tank3->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_tank3->setTextFormat(Qt::AutoText);
        label_tank4 = new QLabel(centralWidget);
        label_tank4->setObjectName(QStringLiteral("label_tank4"));
        label_tank4->setGeometry(QRect(170, 590, 61, 16));
        label_tank4->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_tank4->setTextFormat(Qt::AutoText);
        label_tank5 = new QLabel(centralWidget);
        label_tank5->setObjectName(QStringLiteral("label_tank5"));
        label_tank5->setGeometry(QRect(170, 680, 61, 16));
        label_tank5->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_tank5->setTextFormat(Qt::AutoText);
        label_arm = new QLabel(centralWidget);
        label_arm->setObjectName(QStringLiteral("label_arm"));
        label_arm->setGeometry(QRect(1120, 353, 61, 16));
        label_arm->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_arm->setTextFormat(Qt::AutoText);
        progressBar_tank1 = new QProgressBar(centralWidget);
        progressBar_tank1->setObjectName(QStringLiteral("progressBar_tank1"));
        progressBar_tank1->setGeometry(QRect(19, 356, 211, 23));
        progressBar_tank1->setMinimum(500);
        progressBar_tank1->setMaximum(1200);
        progressBar_tank1->setValue(800);
        progressBar_tank1->setTextVisible(false);
        progressBar_tank2 = new QProgressBar(centralWidget);
        progressBar_tank2->setObjectName(QStringLiteral("progressBar_tank2"));
        progressBar_tank2->setGeometry(QRect(20, 440, 211, 23));
        progressBar_tank2->setMinimum(500);
        progressBar_tank2->setMaximum(1200);
        progressBar_tank2->setValue(800);
        progressBar_tank2->setTextVisible(false);
        progressBar_tank3 = new QProgressBar(centralWidget);
        progressBar_tank3->setObjectName(QStringLiteral("progressBar_tank3"));
        progressBar_tank3->setGeometry(QRect(20, 530, 211, 23));
        progressBar_tank3->setMinimum(500);
        progressBar_tank3->setMaximum(1200);
        progressBar_tank3->setValue(800);
        progressBar_tank3->setTextVisible(false);
        progressBar_tank4 = new QProgressBar(centralWidget);
        progressBar_tank4->setObjectName(QStringLiteral("progressBar_tank4"));
        progressBar_tank4->setGeometry(QRect(20, 620, 211, 23));
        progressBar_tank4->setMinimum(500);
        progressBar_tank4->setMaximum(1200);
        progressBar_tank4->setValue(800);
        progressBar_tank4->setTextVisible(false);
        progressBar_tank5 = new QProgressBar(centralWidget);
        progressBar_tank5->setObjectName(QStringLiteral("progressBar_tank5"));
        progressBar_tank5->setGeometry(QRect(17, 709, 211, 23));
        progressBar_tank5->setMinimum(500);
        progressBar_tank5->setMaximum(1200);
        progressBar_tank5->setValue(800);
        progressBar_tank5->setTextVisible(false);
        progressBar_arm = new QProgressBar(centralWidget);
        progressBar_arm->setObjectName(QStringLiteral("progressBar_arm"));
        progressBar_arm->setGeometry(QRect(962, 380, 211, 23));
        progressBar_arm->setMinimum(500);
        progressBar_arm->setMaximum(1200);
        progressBar_arm->setValue(800);
        progressBar_arm->setTextVisible(false);
        label_time = new QLabel(centralWidget);
        label_time->setObjectName(QStringLiteral("label_time"));
        label_time->setGeometry(QRect(990, 270, 171, 20));
        label_time->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: white;"));
        label_time->setTextFormat(Qt::AutoText);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_bg->setText(QString());
        label->setText(QApplication::translate("MainWindow", "\344\270\273\346\234\272\346\270\251\345\272\246", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\344\270\273\350\275\264\350\275\254\351\200\237", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\345\211\257\350\275\264\350\275\254\351\200\237", Q_NULLPTR));
        labelx->setText(QApplication::translate("MainWindow", "\344\270\273\346\234\272\346\227\266\351\227\264", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "1\345\217\267\345\216\213\345\212\233\350\210\261", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "2\345\217\267\345\216\213\345\212\233\350\210\261", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "3\345\217\267\345\216\213\345\212\233\350\210\261", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "4\345\217\267\345\216\213\345\212\233\350\210\261", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "5\345\217\267\345\216\213\345\212\233\350\210\261", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "1\345\217\267\345\267\245\344\275\234\347\274\270\346\262\271\351\207\217", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "2\345\217\267\345\267\245\344\275\234\347\274\270\346\262\271\351\207\217", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "3\345\217\267\345\267\245\344\275\234\347\274\270\346\262\271\351\207\217", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "\346\234\272\346\242\260\350\207\202\345\216\213\345\212\233\345\200\274", Q_NULLPTR));
        label_temp->setText(QApplication::translate("MainWindow", "000", Q_NULLPTR));
        label_fuel1->setText(QApplication::translate("MainWindow", "000", Q_NULLPTR));
        label_fuel2->setText(QApplication::translate("MainWindow", "000", Q_NULLPTR));
        label_fuel3->setText(QApplication::translate("MainWindow", "000", Q_NULLPTR));
        label_RPM_main->setText(QApplication::translate("MainWindow", "000", Q_NULLPTR));
        label_RPM_sub->setText(QApplication::translate("MainWindow", "000", Q_NULLPTR));
        label_tank1->setText(QApplication::translate("MainWindow", "000 Pa", Q_NULLPTR));
        label_tank2->setText(QApplication::translate("MainWindow", "000 Pa", Q_NULLPTR));
        label_tank3->setText(QApplication::translate("MainWindow", "000 Pa", Q_NULLPTR));
        label_tank4->setText(QApplication::translate("MainWindow", "000 Pa", Q_NULLPTR));
        label_tank5->setText(QApplication::translate("MainWindow", "000 Pa", Q_NULLPTR));
        label_arm->setText(QApplication::translate("MainWindow", "000 Pa", Q_NULLPTR));
        label_time->setText(QApplication::translate("MainWindow", "2023-04-14 00:00:00", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
