#include "Animation.h"
#include <qpainter.h>
#include <qpropertyanimation.h>
#include <qdebug.h>

//�÷ַ�����ͼ
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

//��дboundingRect
QRectF animationMark::boundingRect() const
{
	return QRectF(60.0,-165.0,80.0,30.0);
}

//��дpaint
void animationMark::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
	painter->drawPixmap(boundingRect(),*mark,mark->rect());
    painter->restore();
}
