#include "baseLine.h"
#include <qpainter.h>

baseLine::baseLine(double y):dypos(y)
{

}
baseLine::~baseLine()
{

}
QRectF baseLine::boundingRect()
{
    return QRectF(0.0,dypos-0.5,200.0,1.0);
}
QPainterPath baseLine::shape()
{
    QPainterPath path;
    path.addRect(0.0,dypos-0.5,200.0,1.0);
    return path;
}