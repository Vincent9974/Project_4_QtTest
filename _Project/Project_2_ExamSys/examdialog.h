#ifndef EXAMDIALOG_H
#define EXAMDIALOG_H
#include <QDialog>
#include <QTimer>
#include <QGridLayout>
#include <QTextEdit>
#include <QButtonGroup>
#include <QLabel>
#include <QRadioButton>
#include <QCheckBox>

class ExamDialog : public QDialog
{
    Q_OBJECT
public:
    ExamDialog(QWidget* parent =0);
    void initTimer();
    void initLayout();
    bool initTextEdit();
    void initButtons(); //初始化按键和标签
    bool hasNoSelect(); //看看有没有题目忘记做了?

private:
    QTimer* m_timer; //计时器
    int m_timeGo; //经过时间
    QGridLayout *m_layout; //布局管理器
    QTextEdit* m_textEdit; //题库显示
    QStringList m_answerList;//答案列表

    QButtonGroup *m_btnGroups[9]; //单向按钮分组,10道题
    QLabel *m_titleLabels[10];

    QRadioButton *m_radioA; //判断题
    QRadioButton *m_radioB;

    QRadioButton *m_radioBtns[32]; //单选题按钮
    QCheckBox *m_checkBtns[4];  //多选题按钮


private slots:
    void freshTime();
    void getScore();


};

#endif // EXAMDIALOG_H
