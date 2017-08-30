#ifndef BLOCK_H
#define BLOCK_H

#include <qgraphicsitem.h>
#include "GameController.h"

class GameController;
class Block:public QGraphicsItem
{
public:
	Block(int ichannel, double dlength, double dypos, GameController &gctrl); 
	Block(const Block&);
	~Block();

	//绘制
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void move();//移动

    int getCh() const;
	double getYpos() const;
    double getLength() const;
    double getEnterPos();
    double getExitPos();
    void setEnterPos(double p);
    void setExitPos(double p);

    double calScore(double p1, double p2);//分数
    void setHighlight();    //高亮显示
    void levelup(int level);//升级
	void advance(int);      //更新

private:
    int ichannel;         //所在通道
    double dlength;       //长度
    double dypos;         //位置纵坐标
    double dspeed;        //下落速度
    double enterPos;      //进入坐标
    double exitPos;       //退出坐标
    double score;         //单次得分
    bool isHighlight;     //是否高亮
    GameController &gctrl;//游戏中心控制
};
#endif