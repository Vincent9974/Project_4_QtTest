#ifndef PACKUPDIALOG_H
#define PACKUPDIALOG_H

#include <QDialog>

namespace Ui {
class packUpDialog;
}

class packUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit packUpDialog(QWidget *parent = 0);
    ~packUpDialog();

private:
    Ui::packUpDialog *ui;
};

#endif // PACKUPDIALOG_H
