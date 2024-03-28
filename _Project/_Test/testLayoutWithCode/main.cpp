#include "testlayout.h"

#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QSpacerItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     TestLayout w;

     QFormLayout *headerLayout = new QFormLayout;

     QLabel *nameLabel = new QLabel("姓名: (&N)");
     QLabel *ageLabel = new QLabel("年龄: (&A)");
     QLabel *emailLabel = new QLabel("邮箱: (&E)");
     QLabel *numLabel = new QLabel("门牌号码: ");

     QLineEdit *nameLineEdit = new QLineEdit;
     QLineEdit *ageLineEdit = new QLineEdit;
     QLineEdit *emailLineEdit = new QLineEdit;
     QLineEdit *numLineEdit = new QLineEdit;

     // 设置伙伴关系
     nameLabel->setBuddy(nameLineEdit);
     ageLabel->setBuddy(ageLineEdit);
     emailLabel->setBuddy(emailLineEdit);

     headerLayout->addRow(nameLabel, nameLineEdit);
     headerLayout->addRow(ageLabel, ageLineEdit);
     headerLayout->addRow(emailLabel, emailLineEdit);
     headerLayout->addRow(numLabel, numLineEdit);

     QLabel *sexLabel = new QLabel("性别: ");
     QRadioButton *mBtn = new QRadioButton;
     QRadioButton *wBtn = new QRadioButton;

     mBtn->setText("男");
     wBtn->setText("女");

     QHBoxLayout *sexLayout = new QHBoxLayout;
     sexLayout->addWidget(sexLabel);
     sexLayout->addWidget(mBtn);
     sexLayout->addWidget(wBtn);

     QSpacerItem *spacer = new QSpacerItem(30,30);

     QPushButton *okBtn = new QPushButton("确定");

     QVBoxLayout *mainLayout = new QVBoxLayout(&w);
     mainLayout->addLayout(headerLayout);
     mainLayout->addLayout(sexLayout);
     mainLayout->addItem(spacer);
     mainLayout->addWidget(okBtn);
     mainLayout->setMargin(10);
     mainLayout->setSpacing(20);

     w.setLayout(mainLayout);
     w.show();
     return a.exec();
}
