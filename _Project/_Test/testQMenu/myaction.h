#ifndef MYACTION_H
#define MYACTION_H
#include <QWidgetAction>
#include <QLineEdit>

class MyAction : public QWidgetAction
{
    Q_OBJECT
public:
    MyAction(QObject* parent = 0);

protected:
    QWidget * createWidget(QWidget *parent) override;

signals:
    void getText(const QString& string);

private slots:
    void sendText(const QString& string);

private:
    QLineEdit * lineEdit;
};

#endif // MYACTION_H
