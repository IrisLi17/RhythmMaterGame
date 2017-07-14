#include "GameController.h"
#include "Block.h"
#include "baseLine.h"
#include "ScoreBox.h"
#include "Song.h"
#include <QKeyEvent>
#include <fstream>
#include <QDebug>
#include <assert.h>
#include <qmessagebox.h>
#define MAX 10

GameController::GameController(QGraphicsScene &scene, QObject *parent):QObject(parent),scene(scene),isPause(false)
{
//	vChannels[0] = 0;
//	vChannels[1] = 1;
//	vChannels[2] = 2;
//	vChannels[3] = 3;
//	vChannels[4] = 2;
//	vChannels[5] = 1;
//	vChannels[6] = 0;
//	vChannels[7] = 1;
//	vChannels[8] = 2;
//	vChannels[9] = 3;
//	vLengths[0] = 20.0;
//	vLengths[1] = 10.0;
//	vLengths[2] = 5.0;
//	vLengths[3] = 15.0;
//	vLengths[4] = 10.0;
//	vLengths[5] = 20.0;
//	vLengths[6] = 5.0;
//	vLengths[7] = 10.0;
//	vLengths[8] = 5.0;
//	vLengths[9] = 8.0;
//	vYpos[0] = -200.0;
//	vYpos[1] = -210.0;
//	vYpos[2] = -215.0;
//	vYpos[3] = -230.0;
//	vYpos[4] = -240.0;
//	vYpos[5] = -260.0;
//	vYpos[6] = -265.0;
//	vYpos[7] = -275.0;
//	vYpos[8] = -280.0;
//	vYpos[9] = -288.0;
    inum = 0;
    totalScore = 0.0;
    timer.start( 100 );
    curSong = new song(1);
    //需要改成如果allBlocks里面最后一个位置太靠下就加一个块到allBlocks里面
	//for(int loop = 0; loop<curSong->size(); loop++)
    //{
		Block *temp = new Block(curSong->getChannels()[0],curSong->getLengths()[0],-200-curSong->getLengths()[0],*this);
		allBlocks.append(temp);
		scene.addItem(temp);
		//if(loop ==0)
			curBlock = temp;
	//}
	//curBlock = &(allBlocks[0]);
    bline = new baseLine();      
	//scene.addItem(curBlock);
    scene.addItem(bline);
    scBox = new scoreBox();
    scene.addItem(scBox);
    scene.installEventFilter(this);
    resume();   
}

GameController::~GameController()
{

}
//void test()
//{
//	qDebug()<<"test";
//}
void GameController::resume()
{
    connect(&timer,SIGNAL(timeout()),&scene,SLOT(advance()));
	//for(int i=0;i<10;i++)
	//	allBlocks[i].advance(1);
	isPause = false;
}

void GameController::pause()
{
    disconnect(&timer,SIGNAL(timeout()),&scene,SLOT(advance()));
    isPause = true;
}

void GameController::gameover()
{
    disconnect(&timer, SIGNAL(timeout()), &scene, SLOT(advance())); 
	//delete bline;
	if (QMessageBox::Yes == QMessageBox::information(NULL,
                            tr("Game Over"), tr("New game?"),
                            QMessageBox::Yes | QMessageBox::No,
                            QMessageBox::Yes)) 
	{
		totalScore = 0.0;
        connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
        scene.clear();

        curBlock = new Block(2,200.0,-300.0,*this);
		bline = new baseLine();
        scene.addItem(curBlock);
		scene.addItem(bline);
	}
	else
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
assert: curBlock->getYpos()< bline->getYpos();
	curBlock->setExitPos(bline->getYpos() - curBlock->getYpos());
    totalScore += curBlock->calScore(curBlock->getEnterPos(),curBlock->getExitPos());
    scBox->setScore(totalScore);
}
void GameController::redirect()
{
    if(allBlocks.last()->getYpos()>= -200)
    {
        inum+=1;
        Block *temp = new Block(curSong->getChannels()[inum],curSong->getLengths()[inum],-200-curSong->getLengths()[inum],*this);
        allBlocks.append(temp);
        scene.addItem(temp);
    }
	if(curBlock->getYpos()>0)
	{
		scene.removeItem(curBlock);
		
		delete allBlocks.takeFirst();
		
		if(allBlocks.isEmpty()){
			gameover();
			return;
		}
		curBlock = allBlocks.first();
	}
}
//move all the blocks and redirect curBlock
//void GameController::blockDrop()
//{
    //for (int loop =0; loop<allBlocks.size(); loop++)
    //{
    //    allBlocks[loop].move();
    //}
//    if (curBlock->getYpos()>= 200 && inum < 10)
 //   {
//        inum += 1;
 //       scene.removeItem(curBlock);
 //       curBlock = &Block(vChannels[inum], vLengths[inum], vLengths[inum]);
 //       scene.addItem(curBlock);
  //  }
 //   else if(inum >= 10)
 //   {
//        gameover();
//    }
//
bool GameController::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        handleKeyDown((QKeyEvent*)event);
        //blockDrop();
        return true;
    }
    else if(event->type() == QEvent::KeyRelease)
    {
        handleKeyUp();
        //blockDrop();
        return true;
    }
    else 
    {
        //blockDrop();
        return false;
    }
}

//void GameController::blockEnterline()
//{
 //   handleKeyDown();
//}

//void GameController::blockExitline()
//{
//    handleKeyUp();
//}