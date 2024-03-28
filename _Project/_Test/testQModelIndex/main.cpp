#include <QApplication>
#include <QTreeView>
#include <QStandardItemModel>
#include <QDebug>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    // 标准模型
    QStandardItemModel model;

    //模型的根节点,根节点不可见
    QStandardItem *parentItem = model.invisibleRootItem();

    QStandardItem *item0 = new QStandardItem;
    item0->setText(QString("A"));

    QPixmap pixmap0(50, 50);
    pixmap0.fill(Qt::red);

    item0->setIcon(QIcon(pixmap0));
    item0->setToolTip(QString("A的提示"));

    // 将item0作为父项的子项
    parentItem->appendRow(item0);
    parentItem = item0;

    QStandardItem *item1 = new QStandardItem;
    item1->setText(QString("B"));

    QPixmap pixmap1(50,50);
    pixmap1.fill(Qt::blue);

    item1->setIcon(pixmap1);
    item1->setToolTip(QString("B项"));

    parentItem->appendRow(item1);


    QStandardItem *item2 = new QStandardItem;
    item2->setText(QString("C"));

    QPixmap pixmap2(50,50);
    pixmap1.fill(Qt::green);

    item2->setIcon(pixmap2);
    item2->setToolTip(QString("C项"));

    parentItem->appendRow(item2);



    // 在视图中显示数据
    QTreeView view;
    view.setModel(&model);
    view.show();

    QModelIndex indexA = model.index(0, 0, QModelIndex());
    qDebug() << "indexA row coutn:"
             << model.rowCount(indexA);

    QModelIndex indexB = model.index(0, 0, indexA);
    qDebug() << "indexB text:"
             << model.data(indexB,Qt::EditRole).toString();
    qDebug() << "indexB text:"
             << model.data(indexB,Qt::ToolTipRole).toString();

    return a.exec();
}
