#include "Block.h"
#include <qpainter.h>
#include <iostream>
class GameController;
Block::Block(int ich, double dl, double dyp, GameController &gctrl):ichannel(ich),dlength(dl),dypos(dyp),gctrl(gctrl)
{
	setPos(ich*50.0+25.0,dyp+dl/2);
    dspeed = 2.0;
    enterPos = 0.0;
    exitPos = dl;
}

Block::Block(const Block& b):gctrl(b.gctrl)
{
	ichannel = b.getCh();
	dlength = b.getLength();
	dypos = b.getYpos();
	dspeed = 4.0;
	enterPos = 0.0;
	exitPos = dlength;
}

Block::~Block()
{

}

QRectF Block::boundingRect() const
{
    return QRectF(-26.0,-dlength/2-1,52.0,dlength+2);
}

QPainterPath Block::shape() const
{
    QPainterPath path;
	//QPointF topleftTemp = mapFromScene(QPointF(myblock.topLeft()));
	//QPointF bottomrightTemp = mapFromScene(QPointF(myblock.bottomRight()));
    //path.addRect(topleftTemp.rx(),topleftTemp.ry(),bottomrightTemp.rx()-topleftTemp.rx(),bottomrightTemp.ry()-topleftTemp.ry());
	path.addRect(-25.0,-dlength/2,50.0,dlength);
	return path;
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	std::clog<<"ready to paint block!"<<std::endl;
    painter->save();
    painter->fillPath(shape(), QBrush(QColor(205,80,186)));
    painter->restore();    
}

void Block::move()
{
	
	this->setPos(50.0*ichannel+25.0,pos().ry()+dspeed);
	dypos += dspeed;

}

int Block::getCh() const
{
    return ichannel;
}
double Block::getYpos() const
{
	return dypos;
}

double Block::getLength()const
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
        move();
		gctrl.redirect();
	}
}
//void Block::handleCollision()
//{
//    QList<QGraphicsItem *> collisions = collidingItems();

//}