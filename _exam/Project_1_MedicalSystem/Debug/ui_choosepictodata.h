/********************************************************************************
** Form generated from reading UI file 'choosepictodata.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEPICTODATA_H
#define UI_CHOOSEPICTODATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_choosePicToData
{
public:
    QLineEdit *lineEdit;
    QToolButton *toolButton;

    void setupUi(QWidget *choosePicToData)
    {
        if (choosePicToData->objectName().isEmpty())
            choosePicToData->setObjectName(QStringLiteral("choosePicToData"));
        choosePicToData->resize(400, 300);
        lineEdit = new QLineEdit(choosePicToData);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 70, 321, 20));
        lineEdit->setReadOnly(true);
        toolButton = new QToolButton(choosePicToData);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(350, 70, 38, 19));

        retranslateUi(choosePicToData);

        QMetaObject::connectSlotsByName(choosePicToData);
    } // setupUi

    void retranslateUi(QWidget *choosePicToData)
    {
        choosePicToData->setWindowTitle(QApplication::translate("choosePicToData", "Form", Q_NULLPTR));
        toolButton->setText(QApplication::translate("choosePicToData", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class choosePicToData: public Ui_choosePicToData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEPICTODATA_H
