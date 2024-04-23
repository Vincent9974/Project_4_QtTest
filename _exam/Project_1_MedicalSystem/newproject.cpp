#include "newproject.h"
#include "ui_newproject.h"

newProject::newProject(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::newProject)
{
    ui->setupUi(this);
}

newProject::~newProject()
{
    delete ui;
}
