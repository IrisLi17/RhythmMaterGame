#include "Block.h"
#include <qpainter.h>

class GameController;
Block::Block(int ich, double dl, double dyp, GameController &gctrl):ichannel(ich),dlength(dl),dypos(dyp),gctrl(gctrl)
{
    dspeed = 2.0;
    enterPos = 0.0;
    exitPos = dl;
}

Block::~Block()
{

}

QRectF Block::boundingRect() const
{
    return QRectF(50.0*ichannel,dypos,50.0,dlength);
}

QPainterPath Block::shape()
{
    QPainterPath path;
    path.addRect(50.0*ichannel,dypos,50.0,dlength);
    return path;
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    painter->fillPath(shape(), QBrush(QColor(205,80,186)));
    painter->restore();    
}

//void Block::move()
//{
//    dypos += dspeed;
//}

int Block::getCh()
{
    return ichannel;
}
double Block::getYpos()
{
    return dypos;
}

double Block::getLength()
{
    return dlength;
}

double Block::getEnterPos()
{
    return enterPos;
}

double Block::getExitPos()
{
    return exitPos;
}
void Block::setEnterPos(double p)
{
    enterPos = p;
}

void Block::setExitPos(double p)
{
    exitPos = p;
}

double Block::calScore(double pEnter, double pExit)
{
    if (pEnter <= pExit)
        score = 0;
    else
        score = (pEnter - pExit)/dlength*100;
    return score;
}
void Block::levelup(int level)
{
    switch(level)
    {
        case 1: dspeed = 2.5; break;
        case 2: dspeed = 3.0; break;
        case 3: dspeed = 3.5; break;
        default: dspeed = 2.0;
    }
}

void Block::advance(int step)
{
    if(!step)
        return;
    else
    {
        dypos += dspeed;
    }
}
//void Block::handleCollision()
//{
//    QList<QGraphicsItem *> collisions = collidingItems();

//}