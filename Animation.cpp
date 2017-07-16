#include "Animation.h"
#include <qpainter.h>
#include <qpropertyanimation.h>

animationMark::animationMark(int i)
{
    setPos(100,-150);
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

QRectF animationMark::boundingRect() const
{
    return QRectF(-40.0,-15.0,80.0,30.0);
}

void animationMark::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
	painter->drawPixmap(boundingRect(),*mark,mark->rect());
    painter->restore();
}

void animationMark::display()
{
    QPropertyAnimation animation(this, "pos");
    animation.setDuration(3000);
    animation.setStartValue(QPointF(100,-150));
    animation.setEndValue(QPointF(100,-250));
    
    animation.setEasingCurve(QEasingCurve::OutBounce);
    
    animation.start();    
}