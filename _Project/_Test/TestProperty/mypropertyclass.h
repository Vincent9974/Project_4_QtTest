#ifndef MYPROPERTYCLASS_H
#define MYPROPERTYCLASS_H

#include <QObject>

class MyPropertyClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mask READ mask WRITE setMask NOTIFY maskChanged)
public:
    explicit MyPropertyClass(QObject *parent = nullptr);
    QString mask()const;
    void setMask(QString strMaskNum);
signals:
    void maskChanged(QString str);
public slots:
private:
    QString m_mask;
};

#endif // MYPROPERTYCLASS_H
