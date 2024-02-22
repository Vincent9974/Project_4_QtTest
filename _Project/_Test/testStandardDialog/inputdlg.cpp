#include "inputdlg.h"
#include <QInputDialog>

InputDlg::InputDlg(QWidget* parent):QDialog(parent)
{
    setWindowTitle("输入对话框示例");

    m_nameTitle = new QLabel("姓名：");
    m_sexTitle = new QLabel("性别：");
    m_ageTitle = new QLabel("年龄：");
    m_scoreTitle = new QLabel("打分：");

    m_nameLabel = new QLabel("热巴");
    m_sexLabel = new QLabel("女");
    m_ageLabel = new QLabel("27");
    m_scoreLabel = new QLabel("95.8");

    m_nameBtn = new QPushButton("编辑姓名");
    m_sexBtn = new QPushButton("编辑性别");
    m_ageBtn = new QPushButton("编辑年龄");
    m_scoreBtn = new QPushButton("编辑分数");

    m_mainLayout = new QGridLayout(this);
    m_mainLayout->addWidget(m_nameTitle,0,0);
    m_mainLayout->addWidget(m_nameLabel,0,1);
    m_mainLayout->addWidget(m_nameBtn,0,2);
    m_mainLayout->addWidget(m_sexTitle,1,0);
    m_mainLayout->addWidget(m_sexLabel,1,1);
    m_mainLayout->addWidget(m_sexBtn,1,2);
    m_mainLayout->addWidget(m_ageTitle,2,0);
    m_mainLayout->addWidget(m_ageLabel,2,1);
    m_mainLayout->addWidget(m_ageBtn,2,2);
    m_mainLayout->addWidget(m_scoreTitle,3,0);
    m_mainLayout->addWidget(m_scoreLabel,3,1);
    m_mainLayout->addWidget(m_scoreBtn,3,2);
    m_mainLayout->setSpacing(20); //设置部件间的间隙
    m_mainLayout->setMargin(10);  //设置部件与窗体的间隙

    connect(m_nameBtn,&QPushButton::clicked,
            this,&InputDlg::eidtName);
    connect(m_sexBtn,&QPushButton::clicked,
            this,&InputDlg::editSex);
    connect(m_ageBtn,&QPushButton::clicked,
            this,&InputDlg::editAge);
    connect(m_scoreBtn,&QPushButton::clicked,
            this,&InputDlg::editScore);
}

void InputDlg::eidtName()
{
    bool ok;
    QString sName = QInputDialog::getText(this,
                          "标准字符串输入对话框",
                          "请编辑姓名：",
                          QLineEdit::Normal,
                          m_nameLabel->text(),
                          &ok);
    if(ok && !sName.isEmpty())
        m_nameLabel->setText(sName);
}

void InputDlg::editSex()
{
    bool ok;
    QStringList sexList;
    sexList << "男" << "女" << "未知";
    QString sex = QInputDialog::getItem(this,
                          "标准条目输入对话框",
                          "请选择性别:",
                          sexList,
                          0,
                          false,
                          &ok);
    if(ok && !sex.isEmpty())
        m_sexLabel->setText(sex);
}

void InputDlg::editAge()
{
    bool ok;
    int age = QInputDialog::getInt(this,
                         "标准int数据类型对话框",
                         "请编辑年龄：",
                         m_ageLabel->text().toInt(),
                         0,
                         120,
                         1,
                         &ok);
    if(ok)  m_ageLabel->setText(QString("%1").arg(age));
}

void InputDlg::editScore()
{
    bool ok;
    double score = QInputDialog::getDouble(this,
                          "标准double类型输入对话框",
                          "请打分：",
                          m_scoreLabel->text().toDouble(),
                          0,
                          100,
                          1,
                          &ok);
    if(ok)  m_scoreLabel->setText(QString::number(score));
}
