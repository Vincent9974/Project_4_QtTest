#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    QComboBox* m_languageBox; //多语言选择
    QLabel* m_nameLabel;
    QLabel* m_signLabel;
};

#endif // MAINWINDOW_H
