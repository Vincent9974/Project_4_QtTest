#include "picutrewidget.h"
#include "ui_picutrewidget.h"

picutreWidget::picutreWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::picutreWidget)
{
    ui->setupUi(this);
}

picutreWidget::~picutreWidget()
{
    delete ui;
}
