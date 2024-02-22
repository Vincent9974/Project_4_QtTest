#include <QApplication>
#include <QWidget>
#include <QDebug>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QWidget widget;
    widget.setWindowTitle("Widget窗体");
    //widget.setWindowState(Qt::WindowMaximized);
    //widget.setWindowState(Qt::WindowMinimized);
    //widget.setWindowState(Qt::WindowFullScreen);
    //widget.setWindowState(Qt::WindowNoState);
    //widget.setWindowState(Qt::WindowActive);
    widget.resize(QSize(600,300));
    widget.move(QPoint(0,0));
    qDebug() << widget.x() << widget.y() ;
    widget.show();

    QWidget widget1(0,Qt::FramelessWindowHint | Qt::Dialog);
    widget1.setWindowTitle("Widget窗体");
    //widget1.show();



    return app.exec();

}
