#include "dialog.h"
#include "ui_dialog.h"
#include <QGridLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    createCtrlFrame();
    createContentFrame();

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_ctrlFrame);
    mainLayout->addWidget(m_contentFrame);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::createCtrlFrame()
{
    // 创建控制框架
    m_ctrlFrame = new QFrame;
    m_ctrlFrame->setFrameStyle(QFrame::Sunken | QFrame::Box); // 设置框架样式为凹陷和边框


    // 创建窗口标签和组合框
    m_windowLabel = new QLabel("QPalette::Window:");
    m_windowComboBox = new QComboBox;
    fillColorList(m_windowComboBox); // 填充颜色列表

    connect(m_windowComboBox, SIGNAL(activated(int)), this, SLOT(showWindow(int))); // 连接信号和槽
    m_windowTextLabel = new QLabel("QPalette::WindowText:");
    m_windowTextComboBox = new QComboBox;
    fillColorList(m_windowTextComboBox);
    connect(m_windowTextComboBox, SIGNAL(activated(int)), this, SLOT(showWindowText(int)));

    // 创建按钮标签和组合框
    m_buttonLabel = new QLabel("QPalette::Button:");
    m_buttonComboBox = new QComboBox;
    fillColorList(m_buttonComboBox);
    connect(m_buttonComboBox, SIGNAL(activated(int)), this, SLOT(showButton(int)));

    m_buttonTextLabel = new QLabel("QPalette::ButtonText:");
    m_buttonTextComboBox = new QComboBox;
    fillColorList(m_buttonTextComboBox);
    connect(m_buttonTextComboBox, SIGNAL(activated(int)), this, SLOT(showButtonText(int)));

    // 创建基础标签和组合框
    m_baseLabel = new QLabel("QPalette::Base:");
    m_baseComboBox = new QComboBox;
    fillColorList(m_baseComboBox);
    connect(m_baseComboBox, SIGNAL(activated(int)), this, SLOT(showBase(int)));

    // 将控件添加到布局中
     QGridLayout *mainLayout = new QGridLayout(m_ctrlFrame);
     mainLayout->setSpacing(20); // 设置间距
     mainLayout->addWidget(m_windowLabel, 0, 0);
     mainLayout->addWidget(m_windowComboBox, 0, 1);
     mainLayout->addWidget(m_windowTextLabel, 1, 0);
     mainLayout->addWidget(m_windowTextComboBox, 1, 1);
     mainLayout->addWidget(m_buttonLabel, 2, 0);
     mainLayout->addWidget(m_buttonComboBox, 2, 1);
     mainLayout->addWidget(m_buttonTextLabel, 3, 0);
     mainLayout->addWidget(m_buttonTextComboBox, 3, 1);
     mainLayout->addWidget(m_baseLabel, 4, 0);
     mainLayout->addWidget(m_baseComboBox, 4, 1);
}


void Dialog::fillColorList(QComboBox *comboBox)
{
    QStringList colorList = QColor::colorNames();
    QString color;
    foreach(color, colorList)
    {
        QPixmap pix(QSize(70, 20));
        pix.fill(QColor(color));
        comboBox->addItem(QIcon(pix), NULL);
        comboBox->setIconSize(QSize(70, 20));
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
}

void Dialog::createContentFrame()
{
    // 创建内容框架
    m_contentFrame = new QFrame;
    m_contentFrame->setAutoFillBackground(true); // 设置自动填充背景

    // 创建标签、组合框、文本框和按钮
    m_label1 = new QLabel("请选择一个值");
    m_label2 = new QLabel("请输入字符串");
    m_comboBox1 = new QComboBox;
    m_lineEdit = new QLineEdit;
    m_textEdit = new QTextEdit;
    m_okBtn = new QPushButton(QString("确认"));
    m_cancelBtn = new QPushButton(QString("取消"));
    m_okBtn->setAutoFillBackground(true); // 设置按钮自动填充背景

    // 创建布局管理器
    QGridLayout *topLayout = new QGridLayout;
    topLayout->addWidget(m_label1, 0, 0);
    topLayout->addWidget(m_comboBox1, 0, 1);
    topLayout->addWidget(m_label2, 1, 0);
    topLayout->addWidget(m_lineEdit, 1, 1);
    topLayout->addWidget(m_textEdit, 2, 0, 1, 2);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(m_okBtn);
    bottomLayout->addWidget(m_cancelBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout(m_contentFrame);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);
}

void Dialog::showWindow(int index)
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[index]);
    QPalette p = m_contentFrame->palette();
    p.setColor(QPalette::Window, color);
    m_contentFrame->setPalette(p);
    m_contentFrame->update();
}

void Dialog::showWindowText(int index)
{
    // 获取颜色列表并根据索引选择颜色
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[index]);

    // 获取内容框架的调色板，并设置窗口文本颜色
    QPalette p = m_contentFrame->palette();
    p.setColor(QPalette::WindowText, color);
    m_contentFrame->setPalette(p);

    // 更新内容框架
    m_contentFrame->update();
}

void Dialog::showButton(int index)
{
    // 获取颜色列表并根据索引选择颜色
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[index]);

    // 获取内容框架的调色板，并设置按钮颜色
    QPalette p = m_contentFrame->palette();
    p.setColor(QPalette::Button, color);
    m_contentFrame->setPalette(p);

    // 更新内容框架
    m_contentFrame->update();
}


void Dialog::showButtonText(int index)
{
    // 获取颜色列表并根据索引选择颜色
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[index]);

    // 获取内容框架的调色板，并设置按钮文本颜色
    QPalette p = m_contentFrame->palette();
    p.setColor(QPalette::ButtonText, color);
    m_contentFrame->setPalette(p);

    // 更新内容框架
    m_contentFrame->update();
}

void Dialog::showBase(int index)
{
    // 获取颜色列表并根据索引选择颜色
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[index]);

    // 获取内容框架的调色板，并设置基色
    QPalette p = m_contentFrame->palette();
    p.setColor(QPalette::Base, color);
    m_contentFrame->setPalette(p);

    // 更新内容框架
    m_contentFrame->update();
}

