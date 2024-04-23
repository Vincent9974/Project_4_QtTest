#ifndef REMAKEDIALOG_H
#define REMAKEDIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class remakeDialog;
}

class remakeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit remakeDialog(QWidget *parent = 0);
    ~remakeDialog();

protected:
    void accept() override;

private slots:
    void on_toolButton_clicked();
    void updateProgressBar();
    void ProgressBarStart();

private:
    Ui::remakeDialog *ui;
    QTimer *m_timer;
};

#endif // REMAKEDIALOG_H
