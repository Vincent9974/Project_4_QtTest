#ifndef TEMPLEDIALOG_H
#define TEMPLEDIALOG_H

#include <QDialog>

namespace Ui {
class TempleDialog;
}

class TempleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TempleDialog(QWidget *parent = nullptr);
    ~TempleDialog();

private:
    Ui::TempleDialog *ui;
};

#endif // TEMPLEDIALOG_H
