#include "dialog.h"
#include <QPushButton>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("标准对话框示例");

    m_fileBtn = new QPushButton("文件对话框");
    m_fileLineEdit = new QLineEdit();
    m_colorBtn = new QPushButton("颜色对话框");
    m_colorFrame = new QFrame;
    m_fontBtn = new QPushButton("字体对话框");
    m_fontLineEdit = new QLineEdit("设置字体");


    m_colorFrame->setFrameStyle(QFrame::Box);
    m_colorFrame->setAutoFillBackground(true);

    m_inputBtn = new QPushButton("标准输入对话框:");
    m_msgBtn = new QPushButton("标准消息对话框:");

    m_mainLayout = new QGridLayout(this);
    m_mainLayout->addWidget(m_fileBtn,0,0);
    m_mainLayout->addWidget(m_fileLineEdit,0,1);
    m_mainLayout->addWidget(m_colorBtn,1,0);
    m_mainLayout->addWidget(m_colorFrame,1,1);
    m_mainLayout->addWidget(m_fontBtn,2,0);
    m_mainLayout->addWidget(m_fontLineEdit,2,1);
    m_mainLayout->addWidget(m_inputBtn,3,0);
    m_mainLayout->addWidget(m_msgBtn,3,1);

    connect(m_fileBtn,&QPushButton::clicked,
            this, &Dialog::ShowFileDlg);
    connect(m_colorBtn,&QPushButton::clicked,
            this, &Dialog::ShowColorDlg);
    connect(m_fontBtn,&QPushButton::clicked,
            this, &Dialog::ShowFontDlg);
    connect(m_inputBtn,&QPushButton::clicked,
            this, &Dialog::ShowInputDlg);

}

Dialog::~Dialog()
{
}

void Dialog::ShowFileDlg()
{
    QString sPath = QFileDialog::getOpenFileName(this,
                                 "文件对话框", ".", "C++ files(*.cpp);;"
                                                 "C Files(*.c);;" "Header files(*.h)");

    m_fileLineEdit->setText(sPath);
}

void Dialog::ShowColorDlg()
{
    QColor color = QColorDialog::getColor(Qt::yellow);
    if(color.isValid())
        m_colorFrame->setPalette(QPalette(color));
}

void Dialog::ShowFontDlg()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok);
    if(ok)
        m_fontLineEdit->setFont(font);
}

void Dialog::ShowInputDlg()
{
    m_inputDlg = new InputDlg(this);
    m_inputDlg->show();
}



