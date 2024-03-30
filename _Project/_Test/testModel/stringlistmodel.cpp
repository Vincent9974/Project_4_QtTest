#include "stringlistmodel.h"



int StringListModel::rowCount(const QModelIndex &parent) const
{
    return m_stringList.count();
}

QVariant StringListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())  return QVariant();

    if(index.row() == m_stringList.size()) return QVariant();

    if(role == Qt::DisplayRole || role == Qt::EditRole)
        return m_stringList.at(index.row());
    else
        return QVariant();
}

QVariant StringListModel::headerDate(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

Qt::ItemFlags StringListModel::flags(const QModelIndex &index) const
{
    if(index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool StringListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        m_stringList.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool StringListModel::insertRows(int position, int rows, const QModelIndex &index)
{
    //告知其他组件指定的行开始插入操作
    beginInsertRows(QModelIndex(), position, position + rows -1);
    for(int row = 0; row < rows; ++row)
    {
        m_stringList.insert(position,QString("插入!!!"));
    }
    //告知其他组件完成操作
    endInsertRows();
    return true;
}

bool StringListModel::removeRows(int position, int rows, const QModelIndex &index)
{
    //告知其他组件指定的行开始删除操作
    beginRemoveRows(QModelIndex(), position, position + rows -1);
    for(int row = 0; row < rows; ++row)
    {
        m_stringList.removeAt(position);
    }

    endRemoveRows();
    return true;
}


