#ifndef BLOCK_H
#define BLOCK_H

#include <qgraphicsitem.h>

class GameController;
class Block:public QGraphicsItem
{
public:
    Block(int ichannel, double dlength, double dypos, GameController &gctrl); 
	~Block();
    QRectF boundingRect();
    QPainterPath shape();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void move();
    //void handleCollision();
    void levelup(int level);
private:
    void handleCollision();
    int ichannel;
    double dlength;
    double dypos;
    double dspeed;
    GameController &gctrl;
};
#endif