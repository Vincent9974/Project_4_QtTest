#ifndef NEWPROJECT_H
#define NEWPROJECT_H

#include <QMainWindow>
#include <QString>
#include "selectmodel.h"

namespace Ui {
class newProject;
}

class newProject : public QMainWindow
{
    Q_OBJECT

public:
    explicit newProject(QWidget *parent = 0);
    ~newProject();
    void initModel();
    void showModelName(const QString &modelName);


signals:
     void projectEntered(const QString &projectName, const QString &filePath, const QString &resolution);

private slots:
    void on_toolButtonModel_clicked();

    void on_toolButtonFIlePath_clicked();

    void on_pushButton_clicked();

    void on_pushButtonEnter_clicked();

private:
    Ui::newProject *ui;
    QString m_projectName;
    QString m_filePath;
    QString m_Width;
    QString m_Height;
    selectModel* m_modelDialog;

};

#endif // NEWPROJECT_H
