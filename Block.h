#ifndef BLOCK_H
#define BLOCK_H

#include <qgraphicsitem.h>

class Block:public QGraphicsItem
{
public:
    Block(int ichannel, double dlength, double dypos, GameController &gctrl); 
    QRectF boundingRect();
    QPainterPath shape();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
private:
    void handleCollision();
    int ichannel;
    double dlength;
    double dypos;
    GameController gctrl;
};
#endif