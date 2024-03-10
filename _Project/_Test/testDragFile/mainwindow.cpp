#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if(mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();
        QString filename = urlList.at(0).toLocalFile();
        if(!filename.isEmpty())
        {
            if(filename.right(4) == ".png")
            {
                QTextImageFormat format;
                format.setName(filename);
                ui->textEdit->textCursor().insertImage(format);
                return;
            }
        }
        QFile file(filename);
        if(!file.open((QIODevice::ReadOnly))) return;
        QTextStream in(&file);

        in.setCodec("UTF-8");
        ui->textEdit->setText(in.readAll());
        file.close();
    }

}

