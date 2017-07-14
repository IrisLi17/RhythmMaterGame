#include "ScoreBox.h"
#include <qpainter.h>

scoreBox::scoreBox(QGraphicsItem * parent):score(0.0)
{
    setPos(100,50);
    setPlainText("Score:"+ QString::number(score));
}

scoreBox::~scoreBox()
{
}

void scoreBox::setScore(double s)
{
    score = s;
	setPlainText("Score:"+QString::number(score));
}