#include "fileinfo.h"
#include "ui_fileinfo.h"

FileInfo::FileInfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FileInfo)
{
    ui->setupUi(this);
}

FileInfo::~FileInfo()
{
    delete ui;
}

