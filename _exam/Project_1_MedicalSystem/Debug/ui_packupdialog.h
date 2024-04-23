/********************************************************************************
** Form generated from reading UI file 'packupdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PACKUPDIALOG_H
#define UI_PACKUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_packUpDialog
{
public:
    QDialogButtonBox *buttonBox;
    QToolButton *toolButtonFile1;
    QToolButton *toolButtonFile2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEditFilePath1;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEditFilePath2;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QLabel *label_5;
    QProgressBar *progressBar;

    void setupUi(QDialog *packUpDialog)
    {
        if (packUpDialog->objectName().isEmpty())
            packUpDialog->setObjectName(QStringLiteral("packUpDialog"));
        packUpDialog->resize(655, 444);
        buttonBox = new QDialogButtonBox(packUpDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(210, 400, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        toolButtonFile1 = new QToolButton(packUpDialog);
        toolButtonFile1->setObjectName(QStringLiteral("toolButtonFile1"));
        toolButtonFile1->setGeometry(QRect(560, 60, 38, 19));
        toolButtonFile2 = new QToolButton(packUpDialog);
        toolButtonFile2->setObjectName(QStringLiteral("toolButtonFile2"));
        toolButtonFile2->setGeometry(QRect(560, 220, 38, 19));
        widget = new QWidget(packUpDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 531, 381));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        lineEditFilePath1 = new QLineEdit(widget);
        lineEditFilePath1->setObjectName(QStringLiteral("lineEditFilePath1"));
        lineEditFilePath1->setReadOnly(true);

        verticalLayout->addWidget(lineEditFilePath1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        verticalLayout->addWidget(lineEdit_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        lineEditFilePath2 = new QLineEdit(widget);
        lineEditFilePath2->setObjectName(QStringLiteral("lineEditFilePath2"));
        lineEditFilePath2->setReadOnly(true);

        verticalLayout->addWidget(lineEditFilePath2);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        lineEdit_4 = new QLineEdit(widget);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        verticalLayout->addWidget(lineEdit_4);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        progressBar = new QProgressBar(widget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        verticalLayout->addWidget(progressBar);


        retranslateUi(packUpDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), packUpDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), packUpDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(packUpDialog);
    } // setupUi

    void retranslateUi(QDialog *packUpDialog)
    {
        packUpDialog->setWindowTitle(QApplication::translate("packUpDialog", "Dialog", Q_NULLPTR));
        toolButtonFile1->setText(QApplication::translate("packUpDialog", "...", Q_NULLPTR));
        toolButtonFile2->setText(QApplication::translate("packUpDialog", "...", Q_NULLPTR));
        label->setText(QApplication::translate("packUpDialog", "\345\256\211\350\243\205\345\214\205\345\255\230\346\224\276\350\267\257\345\276\204", Q_NULLPTR));
        label_2->setText(QApplication::translate("packUpDialog", "\345\256\211\350\243\205\345\214\205\350\277\220\350\241\214\346\227\266\347\252\227\345\217\243\346\240\207\351\242\230", Q_NULLPTR));
        label_3->setText(QApplication::translate("packUpDialog", "\345\256\211\350\243\205\345\214\205\350\277\220\350\241\214\346\227\266\347\274\272\347\234\201\345\256\211\350\243\205\350\267\257\345\276\204", Q_NULLPTR));
        label_4->setText(QApplication::translate("packUpDialog", "\345\256\211\350\243\205\345\214\205\345\256\214\346\210\220\345\220\216\347\232\204\345\277\253\346\215\267\346\226\271\345\274\217\345\220\215", Q_NULLPTR));
        label_5->setText(QApplication::translate("packUpDialog", "\346\255\243\345\234\250\346\211\223\345\214\205", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class packUpDialog: public Ui_packUpDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PACKUPDIALOG_H
