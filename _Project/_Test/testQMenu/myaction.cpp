#include "myaction.h"
#include <QSplitter>
#include <QLabel>

MyAction::MyAction(QObject *parent) : QWidgetAction(parent)
{
    lineEdit = new QLineEdit;
    connect(lineEdit, &QLineEdit::textChanged,
            this, &MyAction::sendText);
}


QWidget *MyAction::createWidget(QWidget *parent)
{
    if(parent->inherits("QMenu") || parent->inherits("QToolBar"))
    {
        QSplitter * splitter = new QSplitter(parent);
        QLabel * label = new QLabel("插入文本");
        splitter->addWidget(label);
        splitter->addWidget(lineEdit);
        return splitter;
    }
    return 0;
}


void MyAction::sendText(const QString &string)
{
    emit getText(lineEdit->text());
    lineEdit->clear();
}
