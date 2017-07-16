#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <qtimer.h>
#include <qgraphicsscene.h>
#include <vector>
#include <QtMultimedia\qmediaplayer.h>

//vChannels.assign(clist,clist + sizeof(clist)/sizeof(int));
//vLengths.assign(lenlist,lenlist +sizeof(lenlist)/sizeof(double));

class Block;
class baseLine;
class scoreBox;
class song;

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
	//void level2();
	//void level3();
    void pause();
    void resume();
    void gameover();
	void advance(int);
	void animationStart(int);

protected:
    bool eventFilter(QObject *object, QEvent *event);
	
private:
    void handleKeyDown(QKeyEvent *event);
    void handleKeyUp();
    //void blockDrop();
	
    void judgeCh1();
    void judgeCh2();
    void judgeCh3();
    void judgeCh4();

	int vChannels[10];
	double vLengths[10];
	double vYpos[10];
    int inum;//song中的块进行到哪一个了
    QTimer timer;
	QMediaPlayer *player;
    QGraphicsScene &scene;
    Block *curBlock;
    
    baseLine *bline;
    scoreBox *scBox;
    song *curSong;
    bool alive;
    bool isPause;
	bool isMusic;
    //double totalScore;
};
#endif