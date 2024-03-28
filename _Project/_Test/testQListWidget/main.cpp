#include <QApplication>
#include <QDebug>
#include <QListWidget>
#include <QTreeWidget>
#include <QTableWidget>



int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QListWidget listWidget;

    //给listwidget添加项目
    new QListWidgetItem("天涯", &listWidget);

    QListWidgetItem* listWidgetItem = new QListWidgetItem;
    listWidgetItem->setText("社区");

    QPixmap pixmap(50, 50);
    pixmap.fill(Qt::blue);
    listWidgetItem->setIcon(QIcon(pixmap));
    listWidgetItem->setToolTip("记录美好生活");

    // 部件插入项目
    listWidget.insertItem(1, listWidgetItem);
    // 设置降序排序
    listWidget.sortItems(Qt::DescendingOrder);

    listWidget.show();

    QTreeWidget treeWidget;
    //设置列数
    treeWidget.setColumnCount(2);
    QStringList headers;
    headers << "名字"  << "数量";

    //设置头
    treeWidget.setHeaderLabels(headers);

    //添加项目
    QTreeWidgetItem * item1 = new QTreeWidgetItem(&treeWidget);
    item1->setText(0, "猫");
    QTreeWidgetItem * item11 = new QTreeWidgetItem(item1);
    item11->setText(0,"缅因猫");
    item11->setText(1,"一条");

    //添加项目,指定前一个项目是item1
    QTreeWidgetItem * item2 = new QTreeWidgetItem(&treeWidget,item1);
    item2->setText(0,"狗");

    treeWidget.show();

    //创建表格部件,指定行数列数
    QTableWidget tableWidget(3, 2);
    QTableWidgetItem *tableWidgetItem = new QTableWidgetItem("tom");
    tableWidget.setItem(1,1,tableWidgetItem);

    //创建表头
    QTableWidgetItem *headerV = new QTableWidgetItem("cat");
    tableWidget.setVerticalHeaderItem(0, headerV);
    QTableWidgetItem *headerH = new QTableWidgetItem("what?");
    tableWidget.setHorizontalHeaderItem(0,headerH);
    tableWidget.show();

    return app.exec();
}
