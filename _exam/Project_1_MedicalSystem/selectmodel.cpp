#include "selectmodel.h"
#include "ui_selectmodel.h"

selectModel::selectModel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectModel)
{
    ui->setupUi(this);
}

selectModel::~selectModel()
{
    delete ui;
}
