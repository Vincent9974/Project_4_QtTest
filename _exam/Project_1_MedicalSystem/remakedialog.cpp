#include "remakedialog.h"
#include "ui_remakedialog.h"

remakeDialog::remakeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::remakeDialog)
{
    ui->setupUi(this);
}

remakeDialog::~remakeDialog()
{
    delete ui;
}
