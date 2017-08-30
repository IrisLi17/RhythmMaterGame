#ifndef ANIMATION_H
#define ANIMATION_H

#include <qgraphicsitem.h>

class animationMark: public QGraphicsItem
{
    Q_PROPERTY(QPointF pos READ getPos WRITE setPos)
public:
    animationMark(int);
    ~animationMark();
	QPointF getPos();
	void setPos(QPointF);
	//»æÖÆ
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
private:
	QPointF pos;
    QPixmap* mark;
};

#endif    