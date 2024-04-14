#include <QApplication>
#include <QQuickView>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QQuickView view;
    view.setSource(QUrl("animations.qml"));
    view.show();

    return app.exec();
}
