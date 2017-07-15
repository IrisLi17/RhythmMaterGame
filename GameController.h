#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <qtimer.h>
#include <qgraphicsscene.h>
#include <vector>

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
    QGraphicsScene &scene;
    Block *curBlock;
    QList<Block *> allBlocks;
    baseLine *bline;
    scoreBox *scBox;
    song *curSong;
    bool isPause;
    //double totalScore;
};
#endif