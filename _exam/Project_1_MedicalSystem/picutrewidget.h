#ifndef PICUTREWIDGET_H
#define PICUTREWIDGET_H

#include <QWidget>

namespace Ui {
class picutreWidget;
}

class picutreWidget : public QWidget
{
    Q_OBJECT

public:
    explicit picutreWidget(QWidget *parent = 0);
    ~picutreWidget();

private:
    Ui::picutreWidget *ui;
};

#endif // PICUTREWIDGET_H
