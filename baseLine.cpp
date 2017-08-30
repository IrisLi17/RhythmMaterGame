#include "baseLine.h"
#include <qpainter.h>
#include <iostream>
baseLine::baseLine(double y):dypos(y)
{

}

baseLine::~baseLine()
{

}

//÷ÿ–¥boundingRect
QRectF baseLine::boundingRect() const
{
    return QRectF(0.0,dypos-0.5,200.0,1.0);
}

QPainterPath baseLine::shape()
{
    QPainterPath path;
    path.addRect(0.0,dypos-0.5,200.0,1.0);
    return path;
}

//÷ÿ–¥paint
void baseLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	std::clog<<"ready to paint baseline!"<<std::endl;
    painter->save();
    painter->fillPath(shape(),QBrush(QColor(255,255,255)));
    painter->restore();
}

double baseLine::getYpos()
{
    return dypos;
}