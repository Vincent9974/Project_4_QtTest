#ifndef CHOOSEPICTODATA_H
#define CHOOSEPICTODATA_H

#include <QWidget>

namespace Ui {
class choosePicToData;
}

class choosePicToData : public QWidget
{
    Q_OBJECT

public:
    explicit choosePicToData(QWidget *parent = 0);
    ~choosePicToData();

private:
    Ui::choosePicToData *ui;
};

#endif // CHOOSEPICTODATA_H
