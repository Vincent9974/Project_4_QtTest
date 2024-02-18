#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void ComeOn(QString& str); //信号无需实现
    void ComeOn2(); //测试信号多对一
    void ComeOn3(); //测试信号多对一
    void ComeOn4(); //测试信号多对一

private slots:
    void on_shButton_clicked();

    void on_chButton_clicked();

    void on_wdButton_clicked();

    void ComeGuys(QString& str);

    void ComeChina();

    void ComeHuaxia();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
