#include "mypropertyclass.h"

MyPropertyClass::MyPropertyClass(QObject *parent) : QObject(parent)
{

}

QString MyPropertyClass::mask() const
{
    return m_mask;
}

void MyPropertyClass::setMask(QString strMaskNum)
{
    m_mask = strMaskNum;
    emit maskChanged(strMaskNum);
}
