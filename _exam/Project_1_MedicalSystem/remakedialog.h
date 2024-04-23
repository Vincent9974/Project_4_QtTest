#ifndef REMAKEDIALOG_H
#define REMAKEDIALOG_H

#include <QDialog>

namespace Ui {
class remakeDialog;
}

class remakeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit remakeDialog(QWidget *parent = 0);
    ~remakeDialog();

private:
    Ui::remakeDialog *ui;
};

#endif // REMAKEDIALOG_H
