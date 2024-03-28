#include "msgboxdlg.h"
#include <QMessageBox>

MsgBoxDlg::MsgBoxDlg(QWidget* parent):QDialog(parent)
{
    setWindowTitle("标准信息对话框集合");

    //构造部件
    m_tipLabel = new QLabel("请选择一种消息框");
    m_questionBtn = new QPushButton("问题消息框");
    m_informationBtn = new QPushButton("信息消息框");
    m_warningBtn = new QPushButton("警告消息框");
    m_criticalBtn = new QPushButton("错误消息框");
    m_aboutBtn = new QPushButton("关于消息框");
    m_aboutQtBtn = new QPushButton("关于Qt消息框");

    //布局界面
    m_mainLayout = new QGridLayout(this);
    m_mainLayout->addWidget(m_tipLabel,0,0,1,2);
    m_mainLayout->addWidget(m_questionBtn,1,0);
    m_mainLayout->addWidget(m_informationBtn,1,1);
    m_mainLayout->addWidget(m_warningBtn,2,0);
    m_mainLayout->addWidget(m_criticalBtn,2,1);
    m_mainLayout->addWidget(m_aboutBtn,3,0);
    m_mainLayout->addWidget(m_aboutQtBtn,3,1);

    connect(m_questionBtn,&QPushButton::clicked,
            this,&MsgBoxDlg::showQuestionMsgDlg);
    connect(m_informationBtn,&QPushButton::clicked,
            this,&MsgBoxDlg::showInfoMsgDlg);
    connect(m_warningBtn,&QPushButton::clicked,
            this,&MsgBoxDlg::showWarnMsgDlg);
    connect(m_criticalBtn,&QPushButton::clicked,
            this,&MsgBoxDlg::showCriticalMsgDlg);
    connect(m_aboutBtn,&QPushButton::clicked,
            this,&MsgBoxDlg::showAboutMsgDlg);
    connect(m_aboutQtBtn,&QPushButton::clicked,
            this,&MsgBoxDlg::showAboutQtMsgDlg);

}

void MsgBoxDlg::showQuestionMsgDlg()
{
    m_tipLabel->setText("问题消息框");
    int res = QMessageBox::question(this,
                          "问题消息框",
                          "您已打开问题消息框，是否关闭？",
                          QMessageBox::Ok |
                          QMessageBox::Cancel,
                          QMessageBox::Ok);

    switch (res){
    case QMessageBox::Ok:
        m_tipLabel->setText("问题消息框-确定");
        break;
    case QMessageBox::Cancel:
        m_tipLabel->setText("问题消息框-取消");
        break;
    default:
        break;
    }
}

void MsgBoxDlg::showInfoMsgDlg()
{
    m_tipLabel->setText("信息消息框");
    QMessageBox::information(this,
                             "信息提示框",
                             "这是个信息提示框，我也不知道写点啥？");
}

void MsgBoxDlg::showWarnMsgDlg()
{
    m_tipLabel->setText("警告消息框");
    int res = QMessageBox::warning(this,
                         "警告消息框",
                         "您有未保存的数据，是否保存？",
                         QMessageBox::Save |
                         QMessageBox::Discard |
                         QMessageBox::Cancel,
                         QMessageBox::Save);

    switch(res){
    case QMessageBox::Save:
        m_tipLabel->setText("点击了保存");
        break;
    case QMessageBox::Discard:
        m_tipLabel->setText("点击了忽视");
        break;
    case QMessageBox::Cancel:
        m_tipLabel->setText("点击了取消");
        break;
    default:
        break;
    }
}

void MsgBoxDlg::showCriticalMsgDlg()
{
    m_tipLabel->setText("错误消息框");
    QMessageBox::critical(this,
                          "错误消息框",
                          "发生重大错误！！！");
}

void MsgBoxDlg::showAboutMsgDlg()
{
    m_tipLabel->setText("关于消息框");
    QMessageBox::about(this,
                       "关于",
                       "这是个关于关于的信息。");
}

void MsgBoxDlg::showAboutQtMsgDlg()
{
    m_tipLabel->setText("关于Qt消息框");
    QMessageBox::aboutQt(this,"关于Qt...");
}
