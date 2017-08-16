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

GameController::GameController(QGraphicsScene &scene, QObject *parent):QObject(parent),scene(scene),alive(false),isPause(true),isMusic(false),isPress(false)
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
	if(alive)
		gameover();
    alive = true;
	isPause = false; 
    curSong = new song(1);
    Block *temp = new Block(curSong->getChannels()[0],curSong->getLengths()[0],-300-curSong->getLengths()[0],*this);
    allBlocks.append(temp);
    scene.addItem(temp);
    curBlock = temp;
    bline = new baseLine();      
    scene.addItem(bline);
    scBox = new scoreBox();
    scene.addItem(scBox);    
	player = new QMediaPlayer();
	player->setMedia(QUrl::fromLocalFile(QString("C:\\Users\\lyf\\Documents\\Visual Studio 2012\\Projects\\RhythmMater\\RhythmMater\\1little_star.mp3")));
	//player->setMedia(QUrl::fromLocalFile(QString("C:/Users/lyf/Documents/Visual Studio 2012/Projects/RhythmMater/RhythmMater/4.wav")));
	player->setVolume(30);
	//player->play();
	timer.start(1000/20);
    connect(&timer,SIGNAL(timeout()),&scene,SLOT(advance()));   
	//qDebug()<<player->currentMedia().canonicalUrl().path();
}
void GameController::level2()
{
	if(alive)
		gameover();
    alive = true;
	isPause = false; 
    curSong = new song(2);
    Block *temp = new Block(curSong->getChannels()[0],curSong->getLengths()[0],-300-curSong->getLengths()[0],*this);
    allBlocks.append(temp);
    scene.addItem(temp);
    curBlock = temp;
    bline = new baseLine();      
    scene.addItem(bline);
    scBox = new scoreBox();
    scene.addItem(scBox);    
	player = new QMediaPlayer;
	player->setMedia(QUrl::fromLocalFile(QString("2thu.mp3")));
	player->setVolume(30);
	timer.start(1000/20);
    connect(&timer,SIGNAL(timeout()),&scene,SLOT(advance()));      
}
void GameController::level3()
{
	if(alive)
		gameover();
    alive = true;
	isPause = false; 
    curSong = new song(3);
    Block *temp = new Block(curSong->getChannels()[0],curSong->getLengths()[0],-300-curSong->getLengths()[0],*this);
    allBlocks.append(temp);
    scene.addItem(temp);
    curBlock = temp;
    bline = new baseLine();      
    scene.addItem(bline);
    scBox = new scoreBox();
    scene.addItem(scBox);    
	player = new QMediaPlayer;
	player->setMedia(QUrl::fromLocalFile(QString("3bee.mp3")));
	player->setVolume(30);
	timer.start(1000/20);
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

void GameController::judgeCh1(bool repeat)
{
    if(curBlock->getCh() != 0 ||
        curBlock->getYpos() + curBlock->getLength() < bline->getYpos())
        
		gameover();
    else if(!repeat&&(!isPress))
    {
        curBlock->setEnterPos(bline->getYpos() - curBlock->getYpos());
		isPress = true;
    }
}

void GameController::judgeCh2(bool repeat)
{
    if(curBlock->getCh() != 1 ||
        curBlock->getYpos() + curBlock->getLength() < bline->getYpos())
        gameover();
    else if(!repeat)
    {
        curBlock->setEnterPos(bline->getYpos() - curBlock->getYpos());
    }
}

void GameController::judgeCh3(bool repeat)
{
	if(curBlock->getCh() != 2 ||
        curBlock->getYpos() + curBlock->getLength() < bline->getYpos())
		gameover();
    else if(!repeat)
    {
        curBlock->setEnterPos(bline->getYpos() - curBlock->getYpos());
    }
}

void GameController::judgeCh4(bool repeat)
{
    if(curBlock->getCh() != 3 ||
        curBlock->getYpos() + curBlock->getLength() < bline->getYpos())
		gameover();
    else if(!repeat)
    {
        curBlock->setEnterPos(bline->getYpos() - curBlock->getYpos());
    }
}

void GameController::handleKeyDown(QKeyEvent *event)
{
    if(!isPause&&alive)
	{
        switch(event->key())
        {
		case Qt::Key_1: judgeCh1(event->isAutoRepeat());break;
		case Qt::Key_2: judgeCh2(event->isAutoRepeat());break;
		case Qt::Key_3: judgeCh3(event->isAutoRepeat());break;
		case Qt::Key_4: judgeCh4(event->isAutoRepeat());break;
        case Qt::Key_Space: pause();break;
		default: gameover();break;
        }

	}
	else if(alive&&event->key()==Qt::Key_Space) 
        resume();//press any key to continue
}

void GameController::handleKeyUp(QKeyEvent *event)
{
//assert: curBlock->getYpos()< bline->getYpos();
	if(!isPause&&alive&&event->key()!=Qt::Key_Space)
	{
	    curBlock->setExitPos(bline->getYpos() - curBlock->getYpos());
		double add = curBlock->calScore(curBlock->getEnterPos(),curBlock->getExitPos());
		if(add<30)
		    //QTimer::singleShot(0,this,SLOT(animationStart(1)));
		    animationStart(1);
		else if(add<70)
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
	//可能要先移除mymark
	if(scene.items().indexOf(mymark)!=-1)
		scene.removeItem(mymark);
	atimer = new QTimeLine(1000);
    atimer->setFrameRange(0, 25);
	mymark = new animationMark(i);
    animation = new QGraphicsItemAnimation;
    animation->setItem(mymark);
    animation->setTimeLine(atimer);
	for(int i=0;i<25;i++)
		animation->setPosAt(i,QPointF(100,-150));
    
    //animation.setEasingCurve(QEasingCurve::OutBounce);
	scene.addItem(mymark);
    atimer->start();
	//scene.removeItem(mymark);
	//delete mymark;
	//mymark = NULL;
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
		foreach(Block* w,allBlocks)
		{
			if(totalScore>1000) w->levelup(3);
			else if(totalScore>500) w->levelup(2);
			else if(totalScore>200) w->levelup(1);
		}
	}
}

bool GameController::eventFilter(QObject *object, QEvent *event)
{
	//if(event->type() == QEvent::KeyPress&&(!((QKeyEvent*)event)->isAutoRepeat()))
	if(event->type() == QEvent::KeyPress)
    {
        handleKeyDown((QKeyEvent*)event);
		isPress = true;
        //blockDrop();
        return true;
    }
    else if(event->type() == QEvent::KeyRelease&&(!((QKeyEvent*)event)->isAutoRepeat())&&(isPress))
    //else if(event->type() == QEvent::KeyRelease&&(isPress))
	{
		handleKeyUp((QKeyEvent*)event);
		isPress = false;
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