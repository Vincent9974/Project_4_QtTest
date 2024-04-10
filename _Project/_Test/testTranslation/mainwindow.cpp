#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_languageBox = new QComboBox;
    m_languageBox->addItem("Chinese", "zh");
    m_languageBox->addItem("English", "en");
    m_languageBox->addItem("Latin", "la");
    m_languageBox->addItem("French", "fr");

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

MainWindow::~MainWindow()
{
    delete ui;
}
