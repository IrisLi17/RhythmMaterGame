#include "GameController.h"
#include "Block.h"
#include "baseLine.h"
#include "ScoreBox.h"
#include "Song.h"
#include "Animation.h"
#include <QKeyEvent>
#include <fstream>
#include <QDebug>
#include <assert.h>
#include <qmessagebox.h>
#define MAX 10

GameController::GameController(QGraphicsScene &scene, QObject *parent):QObject(parent),scene(scene),alive(false),isPause(true),isMusic(false)
{
    totalScore = 0.0;
    //timer.start( 1000/33 );
	inum = 0;
	scene.installEventFilter(this);
    //resume();   
}

GameController::~GameController()
{

}
//void test()
//{
//	qDebug()<<"test";
//}

void GameController::level1()
{
    alive = true;
	isPause = false; 
    curSong = new song(1);//怎样传进来
    Block *temp = new Block(curSong->getChannels()[0],curSong->getLengths()[0],-300-curSong->getLengths()[0],*this);
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
    
	player = new QMediaPlayer;
	player->setMedia(QUrl::fromLocalFile(QString("little_star.mp3")));
	player->setVolume(30);
	timer.start(1000/33);
    connect(&timer,SIGNAL(timeout()),&scene,SLOT(advance()));
       
}

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
    
    alive = false;
	//totalScore = 0.0;
	inum = 0;
	if (!(allBlocks.isEmpty()))
	{
		foreach(Block* w,allBlocks)  
		{  
			if(w)  
			{  
				allBlocks.removeOne(w);  
				delete w;  
				w=NULL;  
			}
		} 
	}
	delete curSong;
	//scene.removeItem(bline);
	delete bline;
	//scene.removeItem(scBox);
	delete scBox;
	delete player;
	curBlock = NULL; 	
	curSong = NULL;
    bline = NULL;
	scBox = NULL;
	player = NULL;
	//connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    //scene.clear();
	isPause = true;
	disconnect(&timer, SIGNAL(timeout()), &scene, SLOT(advance())); 
    QMessageBox message(QMessageBox::NoIcon, "Game Over", "Your score: "+QString::number(totalScore)+"\nExit the game?", QMessageBox::Yes | QMessageBox::No, NULL); 
    if(message.exec() == QMessageBox::Yes) 
    { 
        exit(1);
    }
	totalScore = 0.0;
	//}
	//else
	//	exit(0);
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
    if(!isPause&&alive)
        switch(event->key())
        {
		case Qt::Key_1: judgeCh1();break;
		case Qt::Key_2: judgeCh2();break;
		case Qt::Key_3: judgeCh3();break;
		case Qt::Key_4: judgeCh4();break;
        case Qt::Key_Space: pause();break;
		default: gameover();break;
        }
    else if(alive) 
        resume();//press any key to continue
}

void GameController::handleKeyUp()
{
//assert: curBlock->getYpos()< bline->getYpos();
	if(!isPause&&alive)
	{
	    curBlock->setExitPos(bline->getYpos() - curBlock->getYpos());
		double add = curBlock->calScore(curBlock->getEnterPos(),curBlock->getExitPos());
		if(add<50)
		    //QTimer::singleShot(0,this,SLOT(animationStart(1)));
				animationStart(1);
		else if(add<75)
			//QTimer::singleShot(0,this,SLOT(animationStart(2)));
			animationStart(2);
		else
			//QTimer::singleShot(0,this,SLOT(animationStart(3)));
			animationStart(3);
        totalScore += curBlock->calScore(curBlock->getEnterPos(),curBlock->getExitPos());
        //加信号和槽做动画
        scBox->setScore(totalScore);
	}
}

void GameController::animationStart(int i)
{
	animationMark* mymark = new animationMark(i);
	scene.addItem(mymark);
	mymark->display();
	scene.removeItem(mymark);
	delete mymark;
	mymark = NULL;
}

void GameController::redirect()
{
	//if(inum == 0&&(curBlock->getYpos()+curBlock->getLength()) == 0.0)
	if(inum == 0&&(player->state()!=QMediaPlayer::PlayingState))
	{
		player->play();
		isMusic = true;
	}
	
    if(allBlocks.last()->getYpos()>= -300 && inum<curSong->size()-1)
    {
        inum+=1;
		if(inum<curSong->size())
		{
			Block *temp = new Block(curSong->getChannels()[inum],curSong->getLengths()[inum],-300-curSong->getLengths()[inum],*this);
			allBlocks.append(temp);
			scene.addItem(temp);
		}
    }
	if(curBlock->getYpos()>0)
	{
		scene.removeItem(curBlock);
		Block *w = allBlocks.takeFirst();
		delete w;
		w = NULL;
		//if(allBlocks.isEmpty()){
		//	gameover();
			//return;
		//}
		if(!allBlocks.isEmpty())
		    curBlock = allBlocks.first();
		else 
		{
			curBlock = NULL;
			//gameover();
		}
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
	else if(allBlocks.isEmpty()&&alive&&(!isPause))
	{
		gameover();
		return false;
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
//可能应该写scene的advance
void GameController::advance(int step)
{
	if(!step)
		return;
	else if(!allBlocks.size())
		gameover();
	else
	{
		foreach (QGraphicsItem* var,scene.items())
		{
			var->advance(1);
		}
	}
}