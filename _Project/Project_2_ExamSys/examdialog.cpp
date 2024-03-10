#include "examdialog.h"
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QMessageBox>
#include <QTextEdit>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>

ExamDialog::ExamDialog(QWidget* parent):QDialog(parent)
{
    // 设置字体大小
    QFont font;
    font.setPointSize(12);
    setFont(font);

    // 设置窗体背景颜色
    setPalette(QPalette(QColor(209,215,255)));

    setWindowTitle("考试已用时0分0秒");
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    resize(800, 900);

    initTimer();
    initLayout();
    if(!initTextEdit())
    {
        QMessageBox::information(this,"提示", "初始化题库数据文件失败!");
        QTimer::singleShot(0,qApp,SLOT(quit));
    }
    initButtons();
    show();
}

void ExamDialog::initTimer()
{
    m_timeGo =0;
    m_timer = new QTimer(this);
    m_timer->setInterval(1000); //设置间隔1s
    m_timer->start(); //启动计时器

    connect(m_timer,SIGNAL(timeout()),this,SLOT(freshTime()));
    //这行代码使用 connect 函数建立了一个连接，
    //该连接将 m_timer 对象的 timeout 信号与当前对象的 freshTime() 槽函数关联起来。

}

void ExamDialog::initLayout()
{
    m_layout = new QGridLayout(this);
    m_layout->setSpacing(10);
    m_layout->setMargin(10);
}

bool ExamDialog::initTextEdit()
{

    QString filename = "exam.txt";
    QFile file(filename);
    QTextStream stream(&file);
    QStringList strList;
    QString strLine;
    stream.setCodec("UTF-8");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        m_textEdit = new QTextEdit(this);
        m_textEdit->setReadOnly(true);

        QString strText; //保存txt内容
        int nLines = 0;
        while(!stream.atEnd())
        {
            if(nLines == 0)
            {
                stream.readLine();
                nLines ++;
                continue;
            }

            //过滤答案行
            if( (nLines >=6 && (nLines%6==0) && nLines<=6*9) || (nLines==6*9+4))
            {
                strLine = stream.readLine();
                strList = strLine.split(" ");
                m_answerList.append(strList[1]);
                strText += "\n";
                nLines++;
                continue;
            }

            strText += stream.readLine();
            strText +="\n";
            nLines ++;
        }
        m_textEdit->setText(strText);
        m_layout->addWidget(m_textEdit,0,0,1,10);
        file.close();
        return true;
    }
    else
    {
        return false;
    }
}

void ExamDialog::initButtons()
{
    QStringList strList = {"A", "B", "C", "D"};

    for(int i = 0; i < 10; i ++)
    {
        m_titleLabels[i] = new QLabel(this);
        m_titleLabels[i]->setText("第"+QString::number(i+1)+"题");
        m_layout->addWidget(m_titleLabels[i], 1, i);

        //判断题
        if( i == 9)
        {
            m_radioA = new QRadioButton(this);
            m_radioB = new QRadioButton(this);

            m_radioA->setText("正确");
            m_radioB->setText("错误");

            m_layout->addWidget(m_radioA,2,9);
            m_layout->addWidget(m_radioB,3,9);

            m_btnGroups[8] = new QButtonGroup(this);
            m_btnGroups[8]->addButton(m_radioA);
            m_btnGroups[8]->addButton(m_radioB);
            break;
        }

        if(i < 8)
        {
            m_btnGroups[i] = new QButtonGroup(this);
        }

        // 选择题
        for(int j = 0; j < 4; j++)
        {
            if(i == 8)
            {
                //多选题
                m_checkBtns[j] = new QCheckBox(this);
                m_checkBtns[j]->setText(strList.at(j));
                m_layout->addWidget(m_checkBtns[j], 2 + j, 8);
            }
            else
            {
                //单选题
                m_radioBtns[4 * i + j] = new QRadioButton(this);
                m_radioBtns[4 * i + j]->setText(strList.at(j));
                m_layout->addWidget( m_radioBtns[4 * i + j],j+2,i);

                m_btnGroups[i]->addButton(m_radioBtns[4 * i + j]);
            }
        }
    }
    QPushButton *submitBtn = new QPushButton(this);
    submitBtn->setText("提交");
    submitBtn->setFixedSize(100, 35);


    //判分
    connect(submitBtn,SIGNAL(clicked(bool)),this,SLOT(getScore()));
    m_layout->addWidget(submitBtn,6,9);
}

bool ExamDialog::hasNoSelect()
{
    int radioSelects = 0;
    for(int i=0; i<8; i++)
    {
        if(m_btnGroups[i]->checkedButton())
        {
            radioSelects ++;
        }
    }
    if(radioSelects != 8)
    {
        return true;
    }

    int checkSelect = 0;
    for(int i=0; i<4; i++)
    {
        if(m_checkBtns[i]->isChecked())
            checkSelect++;
    }

    if(checkSelect== 0 || checkSelect == 1)
        return true;

    if(!m_radioA->isChecked() &&!m_radioB->isChecked())
        return true;

    return false;
}

void ExamDialog::freshTime()
{
    m_timeGo ++;
    QString minute = QString::number(m_timeGo / 60);
    QString second = QString::number(m_timeGo % 60);
    setWindowTitle("考试已用时: " + minute + "分" + second + "秒");
}

void ExamDialog::getScore()
{
    if(hasNoSelect())
    {
        QMessageBox::information(this,"警告","还有题目没做!");
        return;
    }

    int score = 0;
    for (int i =0 ; i < 10 ; i++) {
        if(i < 8)
        {
            //单选题打分
            if(m_answerList.at(i) == m_btnGroups[i]->checkedButton()->text())
                score += 10;
        }

        //多选题打分
        if(i == 8)
        {
            QString answer = m_answerList.at(i);
            bool hasA = false;
            bool hasB = false;
            bool hasC = false;
            bool hasD = false;

            if(answer.contains("A")) hasA = true;
            if(answer.contains("B")) hasB = true;
            if(answer.contains("C")) hasC = true;
            if(answer.contains("D")) hasD = true;

            bool checkA = m_checkBtns[0]->checkState();
            bool checkB = m_checkBtns[1]->checkState();
            bool checkC = m_checkBtns[2]->checkState();
            bool checkD = m_checkBtns[3]->checkState();

            if(hasA !=checkA) continue;
            if(hasB !=checkB) continue;
            if(hasC !=checkC) continue;
            if(hasD !=checkD) continue;

            score += 10;
        }

        if(i == 9)
        {
            if(m_btnGroups[8]->checkedButton()->text() == m_answerList.at(i))
                score += 10;
        }
    }

    QString str = "分数是:" + QString::number(score) + "分,是否再考一次?";

    int res = QMessageBox::information(this,"提示",str,QMessageBox::Yes | QMessageBox::No);

    if(res == QMessageBox::Yes)
        return;
    else
        close();
}
