#ifndef ANIMATION_H
#define ANIMATION_H

#include <qgraphicsitem.h>

class animationMark: public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    animationMark(int);
    ~animationMark();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void display();
private:
    QPixmap* mark;
};

#endif    