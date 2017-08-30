#include "Block.h"
#include <qpainter.h>
#include <iostream>

class GameController;
Block::Block(int ich, double dl, double dyp, GameController &gctrl):ichannel(ich),dlength(dl),dypos(dyp),gctrl(gctrl)
{
	setPos(ich*50.0+25.0,dyp+dl/2);
    dspeed = 3.0;
    enterPos = 0.0;
    exitPos = dl;
    isHighlight = false;
}

Block::Block(const Block& b):gctrl(b.gctrl)
{
	ichannel = b.getCh();
	dlength = b.getLength();
	dypos = b.getYpos();
	dspeed = 3.0;
	enterPos = 0.0;
	exitPos = dlength;
}

Block::~Block()
{

}

//��дboundingRect
QRectF Block::boundingRect() const
{
    return QRectF(-26.0,-dlength/2-1,52.0,dlength+2);
}

//��дpaint
void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->save();
    if(!isHighlight)
	    painter->drawPixmap(QRectF(-25.0,-dlength/2,50.0,dlength),QPixmap(QString(":/images/block.png")),QRectF(0,0,128,211));
    else
        painter->drawPixmap(QRectF(-25.0,-dlength/2,50.0,dlength),QPixmap(QString(":/images/block_after.png")),QRectF(0,0,129,312));
	painter->restore();
}

//�ı�λ��
void Block::move()
{	
	this->setPos(50.0*ichannel+25.0,pos().ry()+dspeed);
	dypos += dspeed;
}

//����ͨ��
int Block::getCh() const
{
    return ichannel;
}

//����������
double Block::getYpos() const
{
	return dypos;
}

//����С���γ���
double Block::getLength()const
{
	return dlength;
}

//���ؽ������꣨���̰���ʱ)
double Block::getEnterPos()
{
    return enterPos;
}

//�����˳����꣨�����ɿ�ʱ��
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

//���ص÷�
double Block::calScore(double pEnter, double pExit)
{
    if (pEnter <= pExit)
        score = 0;
	else
		score = (pEnter - pExit)/dlength*100;
    return score;
}

void Block::setHighlight()
{
    isHighlight = true;
}

//�����޸��ٶ�
void Block::levelup(int level)
{
    switch(level)
    {
        case 1: dspeed = 3.5; break;
        case 2: dspeed =4.0; break;
        case 3: dspeed = 5.0; break;
        default: dspeed = 3.0;
    }
}

//��дadvance
void Block::advance(int step)
{
    if(!step)
        return;
	else if(gctrl.allBlocks.isEmpty())
		return;
    else
    {
        move();
		gctrl.redirect();
	}
}