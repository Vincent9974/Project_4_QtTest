#include "newproject.h"
#include "ui_newproject.h"
#include "selectmodel.h"
#include <QFileDialog>

newProject::newProject(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::newProject)
{
    ui->setupUi(this);
    m_modelDialog = new selectModel();
    connect(ui->toolButtonModel, &QToolButton::clicked,
            this, &newProject::initModel);


    connect(ui->toolButtonModel, &QToolButton::clicked,
            this, &newProject::initModel);

    connect(m_modelDialog, &selectModel::eimtModelName,
            this, &newProject::showModelName);

}

newProject::~newProject()
{
    delete ui;
}

void newProject::initModel()
{
    m_modelDialog->show();
}

void newProject::showModelName(const QString &modelName)
{
    ui->lineEditSelectModel->setText(modelName);
}



void newProject::on_toolButtonModel_clicked()
{

}

void newProject::on_toolButtonFIlePath_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this,
                                                            "选择文件夹",
                                                            "",
                                                            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEditFilePath->setText(folderPath);
}

void newProject::on_pushButton_clicked()
{
    this->close();
}



void newProject::on_pushButtonEnter_clicked()
{
    QString projectName= ui->lineEditProjectName->text();
    QString filePath = ui->lineEditFilePath->text();
    QString resolution = ui->lineEditWidth->text() + "*" + ui->lineEditHeight->text();
    emit projectEntered(projectName, filePath, resolution);
    this->close();
}
