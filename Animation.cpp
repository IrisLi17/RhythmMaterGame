#include "Animation.h"
#include <qpainter.h>
#include <qpropertyanimation.h>
#include <qdebug.h>

animationMark::animationMark(int i)
{
    setPos(QPointF(100,-150));
    switch(i)
    {
        case 1:
        {
            mark = new QPixmap(QString("good.png"));
            break;
        }
        case 2:
        {
            mark = new QPixmap(QString("cool.png"));
            break;
        }
        case 3:
        {
            mark = new QPixmap(QString("excellent.png"));
            break;
        }
        default: break;
    }
}

animationMark::~animationMark()
{

}
QPointF animationMark::getPos()
{
	return pos;
}

void animationMark::setPos(QPointF p)
{
	pos.setX(p.rx());
	pos.setY(p.ry());
//	qDebug()<<pos.rx()<<','<<pos.ry()<<'\n';
}

QRectF animationMark::boundingRect() const
{
    //return QRectF(-40.0,-15.0,80.0,30.0);
	return QRectF(60.0,-165.0,80.0,30.0);
}

void animationMark::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
	painter->drawPixmap(boundingRect(),*mark,mark->rect());
    painter->restore();
	qDebug()<<pos.rx()<<','<<pos.ry();
}
