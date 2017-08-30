#include "Animation.h"
#include <qpainter.h>
#include <qpropertyanimation.h>
#include <qdebug.h>

//得分反馈贴图
animationMark::animationMark(int i)
{
    setPos(QPointF(100,-150));
    switch(i)
    {
        case 1:
        {
            mark = new QPixmap(QString(":/images/good.png"));
            break;
        }
        case 2:
        {
            mark = new QPixmap(QString(":/images/cool.png"));
            break;
        }
        case 3:
        {
            mark = new QPixmap(QString(":/images/excellent.png"));
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
}

//重写boundingRect
QRectF animationMark::boundingRect() const
{
	return QRectF(60.0,-165.0,80.0,30.0);
}

//重写paint
void animationMark::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
	painter->drawPixmap(boundingRect(),*mark,mark->rect());
    painter->restore();
}
