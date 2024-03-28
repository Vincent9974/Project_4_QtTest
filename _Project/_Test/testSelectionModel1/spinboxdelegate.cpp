#include "spinboxdelegate.h"
#include <QSpinBox>


SpinBoxDelegate::SpinBoxDelegate(QObject *parent)
{

}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSpinBox *edior = new QSpinBox(parent);
    edior->setMinimum(0);
    edior->setMaximum(100);
    return edior;
}

void SpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.model()->data(index,Qt::EditRole).toInt();

    //类型转换: QWidget* 转QSpinBox*
    QSpinBox* spinBox = static_cast<QSpinBox*>(editor);

    //编辑器设置数据
    spinBox->setValue(value);
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}


