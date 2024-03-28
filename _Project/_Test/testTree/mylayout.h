#ifndef MYLAYOUT_H
#define MYLAYOUT_H
#include <QGridLayout>

class MyLayout : public QGridLayout
{
public:
    MyLayout(QWidget* parent = 0);
    ~MyLayout();
};

#endif // MYLAYOUT_H
