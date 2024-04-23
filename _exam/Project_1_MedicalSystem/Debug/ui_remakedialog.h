/********************************************************************************
** Form generated from reading UI file 'remakedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMAKEDIALOG_H
#define UI_REMAKEDIALOG_H

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

QT_BEGIN_NAMESPACE

class Ui_remakeDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLineEdit *lineEditPwd;
    QLabel *label_2;
    QLineEdit *lineEditFilePath;
    QToolButton *toolButton;
    QLabel *label_3;
    QProgressBar *progressBar;

    void setupUi(QDialog *remakeDialog)
    {
        if (remakeDialog->objectName().isEmpty())
            remakeDialog->setObjectName(QStringLiteral("remakeDialog"));
        remakeDialog->resize(491, 344);
        buttonBox = new QDialogButtonBox(remakeDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(130, 290, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(remakeDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 50, 54, 12));
        lineEditPwd = new QLineEdit(remakeDialog);
        lineEditPwd->setObjectName(QStringLiteral("lineEditPwd"));
        lineEditPwd->setGeometry(QRect(30, 80, 381, 31));
        lineEditPwd->setEchoMode(QLineEdit::Password);
        label_2 = new QLabel(remakeDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 130, 54, 12));
        lineEditFilePath = new QLineEdit(remakeDialog);
        lineEditFilePath->setObjectName(QStringLiteral("lineEditFilePath"));
        lineEditFilePath->setGeometry(QRect(30, 150, 381, 31));
        lineEditFilePath->setEchoMode(QLineEdit::Normal);
        lineEditFilePath->setReadOnly(true);
        toolButton = new QToolButton(remakeDialog);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(430, 160, 38, 19));
        label_3 = new QLabel(remakeDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 200, 81, 16));
        progressBar = new QProgressBar(remakeDialog);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(30, 250, 371, 23));
        progressBar->setValue(0);

        retranslateUi(remakeDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), remakeDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), remakeDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(remakeDialog);
    } // setupUi

    void retranslateUi(QDialog *remakeDialog)
    {
        remakeDialog->setWindowTitle(QApplication::translate("remakeDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("remakeDialog", "\345\267\245\347\250\213\345\257\206\347\240\201", Q_NULLPTR));
        label_2->setText(QApplication::translate("remakeDialog", "\345\267\245\347\250\213\350\267\257\345\276\204", Q_NULLPTR));
        toolButton->setText(QApplication::translate("remakeDialog", "...", Q_NULLPTR));
        label_3->setText(QApplication::translate("remakeDialog", "\345\267\245\347\250\213\346\201\242\345\244\215\344\270\255", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class remakeDialog: public Ui_remakeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMAKEDIALOG_H
