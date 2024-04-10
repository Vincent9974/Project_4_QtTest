#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QComboBox* m_languageBox; //多语言选择
    QLabel* m_nameLabel;
    QLabel* m_signLabel;
};

#endif // MAINWINDOW_H
