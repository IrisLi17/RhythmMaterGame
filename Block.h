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

	//����
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void move();//�ƶ�

    int getCh() const;
	double getYpos() const;
    double getLength() const;
    double getEnterPos();
    double getExitPos();
    void setEnterPos(double p);
    void setExitPos(double p);

    double calScore(double p1, double p2);//����
    void setHighlight();    //������ʾ
    void levelup(int level);//����
	void advance(int);      //����

private:
    int ichannel;         //����ͨ��
    double dlength;       //����
    double dypos;         //λ��������
    double dspeed;        //�����ٶ�
    double enterPos;      //��������
    double exitPos;       //�˳�����
    double score;         //���ε÷�
    bool isHighlight;     //�Ƿ����
    GameController &gctrl;//��Ϸ���Ŀ���
};
#endif