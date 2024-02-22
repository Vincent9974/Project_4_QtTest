#ifndef INPUTDLG_H
#define INPUTDLG_H
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class InputDlg : public QDialog
{
    Q_OBJECT
public:
    InputDlg(QWidget* parent = 0);

private slots:
    void eidtName();
    void editSex();
    void editAge();
    void editScore();

private:
   QLabel* m_nameTitle; //姓名：
   QLabel* m_sexTitle;  //性别：
   QLabel* m_ageTitle;
   QLabel* m_scoreTitle;

   QLabel* m_nameLabel; //"热巴"
   QLabel* m_sexLabel;
   QLabel* m_ageLabel;
   QLabel* m_scoreLabel;

   QPushButton* m_nameBtn;
   QPushButton* m_sexBtn;
   QPushButton* m_ageBtn;
   QPushButton* m_scoreBtn;

   QGridLayout* m_mainLayout;   //布局管理器
};

#endif // INPUTDLG_H
