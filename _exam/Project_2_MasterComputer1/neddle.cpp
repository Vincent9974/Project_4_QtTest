#include "neddle.h"
#include <QPainter>

neddle::neddle(QWidget *parent) : QWidget(parent)
{
    //设置窗口大小
    setFixedSize(8, 63);

    //设置背景样式
    //setStyleSheet("background:transparent;");
}

void neddle::paintEvent(QPaintEvent *event)
{
    //创建画刷
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    //导入图片
    QPixmap pix(":/res/neddle.png");

    painter.drawPixmap(this->rect(), pix);
}
