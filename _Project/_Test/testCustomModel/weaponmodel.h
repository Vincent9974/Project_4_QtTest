#ifndef WEAPONMODEL_H
#define WEAPONMODEL_H
#include <QAbstractTableModel>
#include <QVector>

class WeaponModel : public QAbstractTableModel
{
public:
    WeaponModel(QObject* parent = 0);

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation
                        , int role) const;
private:
    QVector<short> army;           //军队
    QVector<short> weaponType;    //武器类型
    QMap<short,QString> armyMap;  //军队映射
    QMap<short,QString> weaponMap; //武器映射

    QStringList weapon; //武器
    QStringList header; //表头

    void populateModel(); //表格数据初始化
};

#endif // WEAPONMODEL_H
