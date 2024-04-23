/********************************************************************************
** Form generated from reading UI file 'selectmodel.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTMODEL_H
#define UI_SELECTMODEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_selectModel
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QRadioButton *radioButton;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QRadioButton *radioButton_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QRadioButton *radioButton_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QRadioButton *radioButton_4;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_5;
    QRadioButton *radioButton_5;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_6;
    QRadioButton *radioButton_6;

    void setupUi(QDialog *selectModel)
    {
        if (selectModel->objectName().isEmpty())
            selectModel->setObjectName(QStringLiteral("selectModel"));
        selectModel->resize(929, 522);
        buttonBox = new QDialogButtonBox(selectModel);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(560, 460, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        widget = new QWidget(selectModel);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(40, 20, 851, 421));
        verticalLayout_7 = new QVBoxLayout(widget);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/res/model.jpg")));

        verticalLayout->addWidget(label);

        radioButton = new QRadioButton(widget);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        verticalLayout->addWidget(radioButton);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/res/model.jpg")));

        verticalLayout_2->addWidget(label_2);

        radioButton_2 = new QRadioButton(widget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        verticalLayout_2->addWidget(radioButton_2);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/res/model.jpg")));

        verticalLayout_3->addWidget(label_3);

        radioButton_3 = new QRadioButton(widget);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));

        verticalLayout_3->addWidget(radioButton_3);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_7->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/res/model.jpg")));

        verticalLayout_4->addWidget(label_4);

        radioButton_4 = new QRadioButton(widget);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));

        verticalLayout_4->addWidget(radioButton_4);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/res/model.jpg")));

        verticalLayout_5->addWidget(label_5);

        radioButton_5 = new QRadioButton(widget);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));

        verticalLayout_5->addWidget(radioButton_5);


        horizontalLayout_2->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/res/model.jpg")));

        verticalLayout_6->addWidget(label_6);

        radioButton_6 = new QRadioButton(widget);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));

        verticalLayout_6->addWidget(radioButton_6);


        horizontalLayout_2->addLayout(verticalLayout_6);


        verticalLayout_7->addLayout(horizontalLayout_2);


        retranslateUi(selectModel);
        QObject::connect(buttonBox, SIGNAL(accepted()), selectModel, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), selectModel, SLOT(reject()));

        QMetaObject::connectSlotsByName(selectModel);
    } // setupUi

    void retranslateUi(QDialog *selectModel)
    {
        selectModel->setWindowTitle(QApplication::translate("selectModel", "Dialog", Q_NULLPTR));
        label->setText(QString());
        radioButton->setText(QApplication::translate("selectModel", "\346\250\241\346\235\277\344\270\200", Q_NULLPTR));
        label_2->setText(QString());
        radioButton_2->setText(QApplication::translate("selectModel", "\346\250\241\346\235\277\344\272\214", Q_NULLPTR));
        label_3->setText(QString());
        radioButton_3->setText(QApplication::translate("selectModel", "\346\250\241\346\235\277\344\270\211", Q_NULLPTR));
        label_4->setText(QString());
        radioButton_4->setText(QApplication::translate("selectModel", "\346\250\241\346\235\277\345\233\233", Q_NULLPTR));
        label_5->setText(QString());
        radioButton_5->setText(QApplication::translate("selectModel", "\346\250\241\346\235\277\344\272\224", Q_NULLPTR));
        label_6->setText(QString());
        radioButton_6->setText(QApplication::translate("selectModel", "\346\250\241\346\235\277\345\205\255", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class selectModel: public Ui_selectModel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTMODEL_H
