#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //单击注册按钮后执行
    QString ret = "dear " + ui->lineEditName->text() +ui->lineEditJob->text() + " welcome!";
    QMessageBox::information(this, "Welcome", ret, QMessageBox::Ok);
}
