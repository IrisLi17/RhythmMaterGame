#ifndef SCOREBOX_H
#define SCOREBOX_H
#include <qgraphicsitem.h>
class scoreBox:public QGraphicsItem
{
public:
    scoreBox();
    ~scoreBox();
    void boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);    

};


#endif