#include "ScoreBox.h"
#include <qpainter.h>

//分数牌
scoreBox::scoreBox(QGraphicsItem * parent):score(0.0)
{
    setPos(80,-200);
	setDefaultTextColor(QColor(255,255,255));
    setPlainText("Score:"+ QString::number(score));
	setFont(QFont("Times",5));
}

scoreBox::~scoreBox()
{
}

//设置分数
void scoreBox::setScore(double s)
{
    score = s;
	setPlainText("Score:"+QString::number(score));
}