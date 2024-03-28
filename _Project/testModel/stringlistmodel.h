#ifndef STRINGLISTMODEL_H
#define STRINGLISTMODEL_H
#include <QAbstractListModel>


class StringListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    StringListModel(const QStringList &strings, QObject *parent =0)
        :QAbstractListModel(parent), m_stringList(strings){}

    //模型行数
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    //指定模型索引的数据项
    QVariant data(const QModelIndex &index, int role) const;

    //表头内容(数或表格)
    QVariant headerDate(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    //项目属性
    Qt::ItemFlags flags(const QModelIndex &index) const;

    //编辑数据
    bool setData(const QModelIndex& index, const QVariant &value,
                 int role = Qt::EditRole);

    //插入行 参数(插入的位置,插入的行数,夫项的模型索引)
    bool insertRows(int position, int rows, const QModelIndex & index=QModelIndex());

    // 删除行
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

private:
    QStringList m_stringList;
};

#endif // STRINGLISTMODEL_H
