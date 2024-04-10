#ifndef GAMESECENE_H
#define GAMESECENE_H

#include <QObject>
#include <QGraphicsScene>
#include "gamescene.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT


public:
    GameScene(QObject* parent, const QRectF &sceneRect);
    ~GameScene();
};

#endif // GAMESECENE_H
