#include <QApplication>
#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QItemSelectionModel>
#include <QDirModel>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QSplitter>
#include <QObject>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // 创建模型
    QDirModel model;

    //创建视图
    QTreeView tree;
    QListView list;
    QTableView table;

    //视图设置模型
    tree.setModel(&model);
    list.setModel(&model);
    table.setModel(&model);

    // 设置视图对象方式为多选,
    tree.setSelectionMode(QAbstractItemView::MultiSelection);
    list.setSelectionMode(tree.selectionMode());
    table.setSelectionMode(tree.selectionMode());


    //树视图双击信号发射后,列表以及表格视图刷新内容
    QObject::connect(&tree, SIGNAL(doubleClicked(QModelIndex)),
                     &list, SLOT(setRootIndex(QModelIndex)));

    QObject::connect(&tree, SIGNAL(doubleClicked(QModelIndex)),
                     &table, SLOT(setRootIndex(QModelIndex)));

    QSplitter* splitter = new QSplitter;
    splitter->addWidget(&tree);
    splitter->addWidget(&list);
    splitter->addWidget(&table);
    splitter->setWindowTitle(QString("模型/视图"));
    splitter->show();

    return app.exec();
}
