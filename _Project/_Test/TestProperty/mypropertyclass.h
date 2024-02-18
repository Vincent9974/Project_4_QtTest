#ifndef MYPROPERTYCLASS_H
#define MYPROPERTYCLASS_H

#include <QObject>

class MyPropertyClass : public QObject
{
    Q_OBJECT
public:
    explicit MyPropertyClass(QObject *parent = nullptr);

signals:

};

#endif // MYPROPERTYCLASS_H
