#include "GameController.h"

GameController::GameController(QGraphicsScene &scene, QObject *parent):QObject(parent),scene(scene)
{
    inum = 0;
    totalScore = 0.0;
    for(int loop = 0; loop<vChannels.size(); loop++)
    {
        allBlocks.append(Block(vChannels[loop], vLengths[loop], vLengths[loop], *this));
        scene.addItem(Block(vChannels[loop], vLengths[loop], vLengths[loop], *this));
    }
    curBlock = allBlocks[0];
    bline = new baseLine(); 

    timer.start( 1000/33 );       
    scene.addItem(bline);
    scene.installEventFilter(this);
    resume();   
}

GameController::~GameController()
{

}
void GameController::resume()
{
    connect(&timer,SIGNAL(timeout()),&scene,SLOT(advance()));
    isPause = false;
}

void GameController::pause()
{
    connect(&timer,SIGNAL(timeout()),&scene,SLOT(advance()));
    isPause = true;
}

void GameController::gameOver()
{
    disconnect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));    
    exit(0);
}

void GameController::judgeCh1()
{
    if(curBlock->getCh() != 0 ||
        curBlock->getYpos() + curBlock->getLength() < bline->getYpos())
        gameover();
    else
    {
        curBlock->setEnterPos(bline->getYpos() - curBlock->getYpos());
    }
}

void GameController::judgeCh2()
{
    if(curBlock->getCh() != 1 ||
        curBlock->getYpos() + curBlock->getLength() < bline->getYpos())
        gameover();
    else
    {
        curBlock->setEnterPos(bline->getYpos() - curBlock->getYpos());
    }
}

void GameController::judgeCh3()
{
    if(curBlock->getCh() != 2 ||
        curBlock->getYpos() + curBlock->getLength() < bline->getYpos())
        gameover();
    else
    {
        curBlock->setEnterPos(bline->getYpos() - curBlock->getYpos());
    }
}

void GameController::judgeCh4()
{
    if(curBlock->getCh() != 3 ||
        curBlock->getYpos() + curBlock->getLength() < bline->getYpos())
        gameover();
    else
    {
        curBlock->setEnterPos(bline->getYpos() - curBlock->getYpos());
    }
}

void GameController::handleKeyDown(QKeyEvent *event)
{
    if(!isPause)
        switch(event->key())
        {
            case Qt::Key_A: judgeCh1();break;
            case Qt::Key_S: judgeCh2();break;
            case Qt::Key_D: judgeCh3();break;
            case Qt::Key_F: judgeCh4();break;
            case Qt::Key_Space: pause();break;
        }
    else resume();//press any key to continue
}

void GameController::handleKeyUp()
{
    if(curBlock->getYpos() + curBlock->getLength() < bline->getYpos())
        gameover();
    else
    {
        curBlock->setExitPos(bline->getYpos() - curBlock->getYpos());
    }
    totalScore += curBlock->calScore(curBlock->getEnterPos(),curBlock->getExitPos());
}

//move all the blocks and redirect curBlock
void GameController::blockDrop()
{
    //for (int loop =0; loop<allBlocks.size(); loop++)
    //{
    //    allBlocks[loop].move();
    //}
    if (curBlock->getYpos()>= 200 && inum < vChannels.size())
    {
        inum += 1;
        scene.removeItem(curBlock);
        curBlock = Block(vChannels[inum], vLengths[inum], vLengths[inum], *this);
        scene.addItem(curBlock);
    }
    else if(inum >= vChannels.size())
    {
        gameover();
    }
}

bool GameController::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        handleKeyDown((QKeyEvent*)event);
        blockDrop();
        return true;
    }
    else if(event->type() == QEvent::KeyRelease)
    {
        handleKeyUp();
        blockDrop();
        return true;
    }
    else 
    {
        blockDrop();
        return eventFilter(object,event);
    }
}

void GameController::blockEnterline()
{
    handleKeyDown();
}

void GameController::blockExitline()
{
    handleKeyUp();
}