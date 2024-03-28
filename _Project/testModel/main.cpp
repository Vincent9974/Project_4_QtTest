#include <QApplication>
#include "stringlistmodel.h"
#include <QListView>
#include <QTableView>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QStringList list;
    list << QString("太阳") << QString("地球") << QString("月亮") << QString("木星");

    StringListModel model(list); // 创建模型
    model.insertRows(3, 2);
    model.removeRows(3, 1);

    QListView listView; // 创建列表视图
    listView.setModel(&model); // 视图设置模型
    listView.show(); // 视图显示

    QTableView tableView; // 创建表格视图
    tableView.setModel(&model); // 视图设置模型
    tableView.show(); // 视图显示

    return app.exec();
}
