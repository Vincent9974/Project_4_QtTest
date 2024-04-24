#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newproject.h"
#include <QTableWidget>
#include "remakedialog.h"
#include "packupdialog.h"
#include "picutrewidget.h"
#include <QVBoxLayout>
#include <QStackedWidget>
#include "choosepictodata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public:
    void handleProjectEntered(const QString &projectName, const QString &filePath, const QString &resolution);
    void initGrid();
    void initPictureList();
    void loadImagesFromFloder(const QString &floderPath);

private slots:
    void on_actionNew_triggered();
    void hadleRemakeAction();
    void hadlePackUpAction();
    void handlePictureView();
    void handlePic2Data();

private:
    Ui::MainWindow *ui;
    newProject* np;
    int m_row ;
    QTableWidget *m_tableWidget;
    remakeDialog *m_remakeDialog;
    packUpDialog *m_packUpDialog;
    picutreWidget *m_pictureWidget;
    QVBoxLayout *m_layout;
    QStackedWidget* m_stackedWidget;
    QString m_imageFilePath;
    choosePicToData *m_choosePic;
};

#endif // MAINWINDOW_H
