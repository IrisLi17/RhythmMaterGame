#include "baseLine.h"
#include <qpainter.h>

baseLine::baseLine(double y):dypos(y)
{

}

baseLine::~baseLine()
{

}

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

void baseLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    painter->fillPath(shape(),QBrush(QColor(0,0,255)));
    painter->restore();
}

double baseLine::getYpos()
{
    return dypos;
}