#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QActionGroup>
#include <QAction>

const int  gTcpPort =  5000;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void loadSettings();
    void saveSettings();
    void onSocketReadyRead();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QActionGroup *m_actionGroup;

    void updateUIFromJson(const QJsonObject &json);
    QJsonObject collectSettings();


};

#endif // MAINWINDOW_H
