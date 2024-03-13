#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTableView;
class QItemSelection;
class QModelIndex;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void getCurrentItemData(); //当前选择
    void toggleSection();  //切换选择

    // 更新选择,selceted表新的选择,deselected表以前的选择
    void updateSelection(const QItemSelection &selseted,
                         const QItemSelection &deselected);

    // 改变当前模型索引
    void changeCurrent(const QModelIndex &current,
                       const QModelIndex &previous);


private:
    Ui::MainWindow *ui;
    QTableView *m_tableView;
    QTableView *m_tableView2;
};
#endif // MAINWINDOW_H
