#include "selectmodel.h"
#include "ui_selectmodel.h"

selectModel::selectModel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectModel)
{
    ui->setupUi(this);
    m_buttonGroup = new QButtonGroup(this);

    m_buttonGroup->addButton(ui->radioButton);
    m_buttonGroup->addButton(ui->radioButton_2);
    m_buttonGroup->addButton(ui->radioButton_3);
    m_buttonGroup->addButton(ui->radioButton_4);
    m_buttonGroup->addButton(ui->radioButton_5);
    m_buttonGroup->addButton(ui->radioButton_6);
}

selectModel::~selectModel()
{
    delete ui;
}


void selectModel::on_buttonBox_accepted()
{
    QString modelName = m_buttonGroup->checkedButton()->text();
    emit eimtModelName(modelName);
}
