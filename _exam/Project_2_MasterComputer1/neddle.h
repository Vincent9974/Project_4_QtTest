#ifndef NEDDLE_H
#define NEDDLE_H

#include <QWidget>

class neddle : public QWidget
{
    Q_OBJECT
public:
    explicit neddle(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // NEDDLE_H
