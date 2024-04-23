#ifndef NEWPROJECT_H
#define NEWPROJECT_H

#include <QMainWindow>

namespace Ui {
class newProject;
}

class newProject : public QMainWindow
{
    Q_OBJECT

public:
    explicit newProject(QWidget *parent = 0);
    ~newProject();

private:
    Ui::newProject *ui;
};

#endif // NEWPROJECT_H
