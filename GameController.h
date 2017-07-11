#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <qtimer.h>
#include <qgraphicsscene.h>
#include <vector>

int clist[10] = {0,1,2,3,2,1,0,1,2,3};
double lenlist[10] = {10.0,15.0,8.0,12.0,5.0,1.0,1.0,2.0,1.0,10.0};
std::vector<int> vChannels;
std::vector<double> vLengths;
vChannels.assign(clist,clist + sizeof(clist)/sizeof(int));
vLengths.assign(lenlist,lenlist +sizeof(lenlist)/sizeof(double));

class Block;
class baseLine;
class GameController:public QObject
{
    Q_OBJECT

public:
    GameController(QGraphicsScene &scene, QObject *parent = 0);
    ~GameController();
    void blockEnterline();
    void blockExitline();

private slots:
    void pause();
    void resume();
    void gameover();

protected:
    bool eventFilter(QObject *object, QEvent *event);

private:
    void handleKeyDown(QEvent *event);
    void handleKeyUp();
    void blockDrop();
    void judgeCh1();
    void judgeCh2();
    void judgeCh3();
    void judgeCh4();

    int inum;
    QTimer timer;
    QGraphicsScene &scene;
    Block *curBlock;
    QList<Block> allBlocks;
    baseLine *bline;
    bool isPause;
    double totalScore;
};
#endif