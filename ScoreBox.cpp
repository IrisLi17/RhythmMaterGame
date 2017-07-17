#include "ScoreBox.h"
#include <qpainter.h>

scoreBox::scoreBox(QGraphicsItem * parent):score(0.0)
{
    setPos(80,-200);
	setDefaultTextColor(QColor(255,255,255));
    setPlainText("Score:"+ QString::number(score));
	setFont(QFont("Times",5));
	//setHtml("<p style=color:aliceblue>Score:</p>"); 
}

scoreBox::~scoreBox()
{
}

void scoreBox::setScore(double s)
{
    score = s;
	setPlainText("Score:"+QString::number(score));
}