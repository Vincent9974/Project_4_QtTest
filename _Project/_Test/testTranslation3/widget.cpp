#include "widget.h"
#include <QVBoxLayout>

/*
 * tr()函数获取翻译的文本
 * lupdate.exe 编译生成xxx.ts文件
 * liguist.exe 进行翻译
 * lrelease.exe生成xxx.qm文件
 * 使用
 * */

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
//    m_languageBox = new QComboBox;
//    m_languageBox->addItem("Chinese", "zh");
//    m_languageBox->addItem("English", "en");
//    m_languageBox->addItem("Latin", "la");
//    m_languageBox->addItem("French", "fr");

    //tr()函数获取需要翻译的文本
    m_nameLabel = new QLabel(tr("Vincent"));
    m_signLabel = new QLabel(tr("C++"));

    setWindowTitle(tr("Translation"));
    resize(400, 100);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_languageBox);
    layout->addWidget(m_nameLabel);
    layout->addWidget(m_signLabel);
    setLayout(layout);
}

Widget::~Widget()
{
}
