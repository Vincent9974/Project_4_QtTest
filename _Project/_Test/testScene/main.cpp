#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    //新建场景
    QGraphicsScene scene;

    //创建矩形图形项
    QGraphicsRectItem* item = new QGraphicsRectItem(0,0,100,100);
    scene.addItem(item);

    QGraphicsView view(&scene); //为场景创建视图
    view.resize(400, 400);
    view.show();

    return app.exec();
}
