#ifndef BLOCK_H
#define BLOCK_H

#include <qgraphicsitem.h>

class GameController;
class Block:public QGraphicsItem
{
public:
    Block(int ichannel, double dlength, double dypos, GameController &gctrl); 
	~Block();
    QRectF boundingRect() const;
    QPainterPath shape();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    //void move();
    int getCh();
    double getYpos();
    double getLength();
    double getEnterPos();
    double getExitPos();
    void setEnterPos(double p);
    void setExitPos(double p);
    double calScore(double p1, double p2);
    //void handleCollision();
    void levelup(int level);

protected:
    void advance(int step);

private:
    //void handleCollision();
    int ichannel;
    double dlength;
    double dypos;
    double dspeed;
    double enterPos;
    double exitPos;
    double score;
    GameController &gctrl;
};
#endif