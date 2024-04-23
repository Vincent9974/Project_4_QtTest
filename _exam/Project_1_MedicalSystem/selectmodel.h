#ifndef SELECTMODEL_H
#define SELECTMODEL_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class selectModel;
}

class selectModel : public QDialog
{
    Q_OBJECT

public:
    explicit selectModel(QWidget *parent = 0);
    ~selectModel();

signals:
    void eimtModelName(const QString &modelName);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::selectModel *ui;
    QButtonGroup *m_buttonGroup;
};

#endif // SELECTMODEL_H
