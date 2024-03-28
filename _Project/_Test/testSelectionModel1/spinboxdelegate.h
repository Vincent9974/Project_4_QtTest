#ifndef SPINBOXDELEGATE_H
#define SPINBOXDELEGATE_H
#include <QItemDelegate>

class SpinBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    SpinBoxDelegate(QObject* parent = 0);

    //创建编辑器
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const override;

    //设置编辑器数据
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    //更新编辑器几何属性
    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

};

#endif // SPINBOXDELEGATE_H
