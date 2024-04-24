#ifndef CHOOSEPICTODATA_H
#define CHOOSEPICTODATA_H


#include <QMainWindow>

namespace Ui {
class choosePicToData;
}

class choosePicToData : public QMainWindow
{
    Q_OBJECT

public:
    explicit choosePicToData(QWidget *parent = 0);
    ~choosePicToData();
    bool copyFile(const QString& sourceFile, const QString& destinationFolder);
    void runPythonScript();
    bool executeCommand(const std::string& command);

private slots:
    void on_toolButton_clicked();

private:
    Ui::choosePicToData *ui;
    QString m_destinationFolder;
    QString m_interpreterPath; //python解释器地址
    QString m_scriptPath;      //脚本地址

};

#endif // CHOOSEPICTODATA_H
