#include "packupdialog.h"
#include "ui_packupdialog.h"
#include <QFileDialog>
#include <QTimer>

packUpDialog::packUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::packUpDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("工程打包");

    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &packUpDialog::updateProgressBar);
}

packUpDialog::~packUpDialog()
{
    delete ui;
}

void packUpDialog::accept()
{

}

void packUpDialog::on_toolButtonFile1_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this,
                                                            "选择文件夹",
                                                            "",
                                                            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEditFilePath1->setText(folderPath);
}

void packUpDialog::on_toolButtonFile2_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this,
                                                            "选择文件夹",
                                                            "",
                                                            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEditFilePath2->setText(folderPath);
}

void packUpDialog::updateProgressBar()
{
    //重置进度条
    ui->progressBar->setValue(0);


    m_timer = new QTimer(this);
    int interval = 30; //定时30ms
    m_timer->start(interval);


    connect(m_timer, &QTimer::timeout,
            this, &packUpDialog::ProgressBarStart);


}

void packUpDialog::ProgressBarStart()
{
    int value = ui->progressBar->value();
    int maxValue = 100;

    value += 1;

    // 如果达到最大值，停止计时器
    if (value >= maxValue) {
        ui->progressBar->setValue(maxValue);
        m_timer->stop();
    } else {
        // 更新进度条的值
        ui->progressBar->setValue(value);
    }
}
