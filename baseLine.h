#ifndef BASELINE_H
#define BASELINE_H

#include <qgraphicsitem.h>

class baseLine:public QGraphicsItem
{
public:
    baseLine(double y = 1.0);
    QRect boundingRect();
    QPainterPath shape();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
private:
    double dypos;
};
#endif