#include "packupdialog.h"
#include "ui_packupdialog.h"

packUpDialog::packUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::packUpDialog)
{
    ui->setupUi(this);
}

packUpDialog::~packUpDialog()
{
    delete ui;
}
