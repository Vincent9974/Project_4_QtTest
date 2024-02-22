#include "templedialog.h"
#include "ui_templedialog.h"

TempleDialog::TempleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TempleDialog)
{
    ui->setupUi(this);
}

TempleDialog::~TempleDialog()
{
    delete ui;
}
