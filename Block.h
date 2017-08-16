#ifndef BLOCK_H
#define BLOCK_H

#include <qgraphicsitem.h>
#include "GameController.h"

class GameController;
class Block:public QGraphicsItem
{
public:
	Block(int ichannel, double dlength, double dypos, GameController &gctrl); 
	Block(const Block&);
	~Block();
    QRectF boundingRect() const;
    //QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void move();
    int getCh() const;
	double getYpos() const;
    double getLength() const;
    double getEnterPos();
    double getExitPos();
    void setEnterPos(double p);
    void setExitPos(double p);
    double calScore(double p1, double p2);
    void setHighlight();
    //void handleCollision();
    void levelup(int level);
	void advance(int);

protected:
    //void advance(int);

private:
    //void handleCollision();
	//QRectF myblock;
    int ichannel;
    double dlength;
    double dypos;
    double dspeed;
    double enterPos;
    double exitPos;
    double score;
    bool isHighlight;
    GameController &gctrl;
};
#endif