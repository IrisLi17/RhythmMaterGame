#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <qtimer.h>
#include <qgraphicsscene.h>
#include <vector>
#include <QtMultimedia\qmediaplayer.h>
#include <qtimeline.h>
#include <qgraphicsitemanimation.h>

class Block;
class baseLine;
class scoreBox;
class song;
class animationMark;

//游戏中心控制
class GameController:public QObject
{
    Q_OBJECT

public:
    GameController(QGraphicsScene &scene, QObject *parent = 0);
    ~GameController();
    void redirect();//更新视图中的数据

	double totalScore;//总分
	QList<Block *> allBlocks;//视图中所有小矩形块
	
public slots:
	void level1();//关卡1
	void level2();//关卡2
	void level3();//关卡3
    void pause(); //暂停
    void resume();//继续
    void gameover();
	void advance(int);       //重写更新
	void animationStart(int);//得分反馈

protected:
    bool eventFilter(QObject *object, QEvent *event);
	
private:
    void handleKeyDown(QKeyEvent *event);
    void handleKeyUp(QKeyEvent*event);
	
	void judgeCh1(bool);
    void judgeCh2(bool);
    void judgeCh3(bool);
    void judgeCh4(bool);

    int inum;//当前allBlocks中最后一个block在所有block中的序号

	QTimer timer;
	QTimeLine *atimer;

	//场景里的东西
    QGraphicsScene &scene;
    Block *curBlock;    
    baseLine *bline;
    scoreBox *scBox;
    song *curSong;
	QGraphicsItemAnimation* animation;
	animationMark* mymark;

    bool alive;
    bool isPause;
	bool isPress;
};
#endif