#ifndef SCOREBOX_H
#define SCOREBOX_H
#include <qgraphicsitem.h>
class scoreBox:public QGraphicsTextItem
{
public:
    scoreBox(QGraphicsItem * parent = 0);
    ~scoreBox();
    void setScore(double);  

private:
    double score;
};


#endif