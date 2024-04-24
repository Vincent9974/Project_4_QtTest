#include "choosepictodata.h"
#include "ui_choosepictodata.h"
#include <QFileDialog>
#include <QDebug>
#include <QDir>
#include <QProcess>
#include <cstdlib>
#include <iostream>
#include <windows.h>

choosePicToData::choosePicToData(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::choosePicToData)
{
    ui->setupUi(this);
    m_destinationFolder = QString("F:\\UserData\\Documents\\GitHubRepo\\PythonTest\\ExcelVision\\image");
    m_interpreterPath = QString("C:\\Users\\Vincent\\anaconda3\\envs\\py37\\python.exe");
    m_scriptPath = QString("F:\\UserData\\Documents\\GitHubRepo\\PythonTest\\ExcelVision\\main.py");
}

choosePicToData::~choosePicToData()
{
    delete ui;
}

bool choosePicToData::copyFile(const QString &sourceFile, const QString &destinationFolder)
{
    // 创建目标文件夹
    QDir dir(destinationFolder);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qWarning() << "Failed to create destination folder:" << destinationFolder;
            return false;
        }
    }

    // 获取源文件名
    QString fileName = QFileInfo(sourceFile).fileName();

    // 构建目标文件路径
    QString destinationFile = QDir(destinationFolder).filePath(fileName);

    // 复制文件
    if (QFile::copy(sourceFile, destinationFile)) {
        qDebug() << "File copied successfully.";
        return true;
    } else {
        qWarning() << "Failed to copy file:" << sourceFile;
        return false;
    }

}

bool choosePicToData::executeCommand(const std::string &command)
{
    int result = system(command.c_str());
    return result == 0; // 如果返回值为0，表示命令执行成功
}

void choosePicToData::runPythonScript()
{



    ShellExecute(NULL, L"runas", L"cmd.exe", L"/c conda run -n py37 python F:/UserData/Documents/GitHubRepo/PythonTest/ExcelVision/main.py", NULL, SW_SHOWNORMAL);

    //system("conda run -n py37 python F:/UserData/Documents/GitHubRepo/PythonTest/ExcelVision/main.py");
    //system("pause");
}

void choosePicToData::on_toolButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("选择图片文件"), "", tr("图片文件 (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if (!fileName.isEmpty()) {
        // 处理选定的文件，例如显示文件路径或加载图像等操作
    }
    ui->lineEdit->setText(fileName);
    qDebug() << fileName;

    copyFile(fileName, m_destinationFolder);
    runPythonScript();
}
