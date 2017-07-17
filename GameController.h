#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <qtimer.h>
#include <qgraphicsscene.h>
#include <vector>
#include <QtMultimedia\qmediaplayer.h>
#include <qtimeline.h>
#include <qgraphicsitemanimation.h>

//vChannels.assign(clist,clist + sizeof(clist)/sizeof(int));
//vLengths.assign(lenlist,lenlist +sizeof(lenlist)/sizeof(double));

class Block;
class baseLine;
class scoreBox;
class song;
class animationMark;

//need to associate song to the game
class GameController:public QObject
{
    Q_OBJECT

public:
    GameController(QGraphicsScene &scene, QObject *parent = 0);
    ~GameController();
    void redirect();
	double totalScore;
	QList<Block *> allBlocks;
	//void blockEnterline();
    //void blockExitline();
	
public slots:
    //void start();
	void level1();
	void level2();
	void level3();
    void pause();
    void resume();
    void gameover();
	void advance(int);
	void animationStart(int);

protected:
    bool eventFilter(QObject *object, QEvent *event);
	
private:
    void handleKeyDown(QKeyEvent *event);
    void handleKeyUp(QKeyEvent*event);
    //void blockDrop();
	
	void judgeCh1(bool);
    void judgeCh2(bool);
    void judgeCh3(bool);
    void judgeCh4(bool);

	int vChannels[10];
	double vLengths[10];
	double vYpos[10];
    int inum;//song中的块进行到哪一个了
    QTimer timer;
	QTimeLine *atimer;
	QMediaPlayer *player;
    QGraphicsScene &scene;
    Block *curBlock;
    
    baseLine *bline;
    scoreBox *scBox;
    song *curSong;
	QGraphicsItemAnimation* animation;
	animationMark* mymark;

    bool alive;
    bool isPause;
	bool isMusic;
	bool isPress;
    //double totalScore;
};
#endif