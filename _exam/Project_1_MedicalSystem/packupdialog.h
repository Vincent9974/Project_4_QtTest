#ifndef PACKUPDIALOG_H
#define PACKUPDIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class packUpDialog;
}

class packUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit packUpDialog(QWidget *parent = 0);
    ~packUpDialog();

protected:
    void accept() override;

private slots:
    void on_toolButtonFile1_clicked();

    void on_toolButtonFile2_clicked();

    void updateProgressBar();

    void ProgressBarStart();

private:
    Ui::packUpDialog *ui;
    QTimer *m_timer;
};

#endif // PACKUPDIALOG_H
