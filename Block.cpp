#include "Block.h"
#include <qpainter.h>

class GameController;
Block::Block(int ich, double dl, double dyp, GameController &gctrl):ichannel(ich),dlength(dl),dypos(dyp),gctrl(gctrl)
{
    dspeed = 2.0;
}

Block::~Block()
{

}

QRectF Block::boundingRect()
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

void Block::move()
{
    dypos += dspeed;
}

void Block::levelup(int level)
{
    switch(level)
    {
        case 1: dspeed = 2.5;break;
        case 2: dspeed = 3.0;break;
        case 3: dspeed = 3.5;break;
        default: dspeed = 2.0;
    }
}

//void Block::handleCollision()
//{
//    QList<QGraphicsItem *> collisions = collidingItems();

//}