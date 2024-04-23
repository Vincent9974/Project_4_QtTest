/********************************************************************************
** Form generated from reading UI file 'picutrewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICUTREWIDGET_H
#define UI_PICUTREWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_picutreWidget
{
public:

    void setupUi(QWidget *picutreWidget)
    {
        if (picutreWidget->objectName().isEmpty())
            picutreWidget->setObjectName(QStringLiteral("picutreWidget"));
        picutreWidget->resize(535, 408);

        retranslateUi(picutreWidget);

        QMetaObject::connectSlotsByName(picutreWidget);
    } // setupUi

    void retranslateUi(QWidget *picutreWidget)
    {
        picutreWidget->setWindowTitle(QApplication::translate("picutreWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class picutreWidget: public Ui_picutreWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICUTREWIDGET_H
