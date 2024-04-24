#include "choosepictodata.h"
#include "ui_choosepictodata.h"

choosePicToData::choosePicToData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choosePicToData)
{
    ui->setupUi(this);
}

choosePicToData::~choosePicToData()
{
    delete ui;
}
