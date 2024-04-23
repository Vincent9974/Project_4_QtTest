#ifndef SELECTMODEL_H
#define SELECTMODEL_H

#include <QDialog>

namespace Ui {
class selectModel;
}

class selectModel : public QDialog
{
    Q_OBJECT

public:
    explicit selectModel(QWidget *parent = 0);
    ~selectModel();

private:
    Ui::selectModel *ui;
};

#endif // SELECTMODEL_H
