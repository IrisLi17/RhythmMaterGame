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

GameController::GameController(QGraphicsScene &scene, QObject *parent):QObject(parent),scene(scene),alive(false),isPause(true),isPress(false)
{
    totalScore = 0.0;
	inum = 0;
	scene.installEventFilter(this);  
}

GameController::~GameController()
{

}

//新建第一关卡
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
	timer.start(1000/20);
    connect(&timer,SIGNAL(timeout()),&scene,SLOT(advance()));   
}

//新建第二关卡
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
	timer.start(1000/20);
    connect(&timer,SIGNAL(timeout()),&scene,SLOT(advance()));      
}

//新建第三关卡
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
	timer.start(1000/20);
    connect(&timer,SIGNAL(timeout()),&scene,SLOT(advance()));      
}

//游戏继续
void GameController::resume()
{
    connect(&timer,SIGNAL(timeout()),&scene,SLOT(advance()));
	isPause = false;
}

//游戏暂停
void GameController::pause()
{
    disconnect(&timer,SIGNAL(timeout()),&scene,SLOT(advance()));
    isPause = true;
}

//游戏结束
void GameController::gameover()
{
    
    alive = false;
	inum = 0;

	//清理allBlocks
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

	//清理工作
	delete curSong;
	delete bline;
	delete scBox;
	curBlock = NULL; 	
	curSong = NULL;
    bline = NULL;
	scBox = NULL;

	isPause = true;

	//取消计时器
	disconnect(&timer, SIGNAL(timeout()), &scene, SLOT(advance())); 

	//弹出消息框
    QMessageBox message(QMessageBox::NoIcon, "Game Over", "Your score: "+QString::number(totalScore)+"\nExit the game?", QMessageBox::Yes | QMessageBox::No, NULL); 
    if(message.exec() == QMessageBox::Yes) 
    { 
        exit(1);
    }

	totalScore = 0.0;
}

//按下1键的处理
void GameController::judgeCh1(bool repeat)
{
    if(curBlock->getCh() != 0 ||
        curBlock->getYpos() + curBlock->getLength() < bline->getYpos())       
		gameover();
    else if(!repeat&&(!isPress))
    {
        curBlock->setEnterPos(bline->getYpos() - curBlock->getYpos());
		curBlock->setHighlight();
		isPress = true;
    }
}

//按下2键的处理
void GameController::judgeCh2(bool repeat)
{
    if(curBlock->getCh() != 1 ||
        curBlock->getYpos() + curBlock->getLength() < bline->getYpos())
        gameover();
    else if(!repeat&&(!isPress))
    {
        curBlock->setEnterPos(bline->getYpos() - curBlock->getYpos());
		curBlock->setHighlight();
		isPress = true;
    }
}

//按下3键的处理
void GameController::judgeCh3(bool repeat)
{
	if(curBlock->getCh() != 2 ||
        curBlock->getYpos() + curBlock->getLength() < bline->getYpos())
		gameover();
    else if(!repeat&&(!isPress))
    {
        curBlock->setEnterPos(bline->getYpos() - curBlock->getYpos());
		curBlock->setHighlight();
		isPress = true;
    }
}

//按下4键的处理
void GameController::judgeCh4(bool repeat)
{
    if(curBlock->getCh() != 3 ||
        curBlock->getYpos() + curBlock->getLength() < bline->getYpos())
		gameover();
    else if(!repeat&&(!isPress))
    {
        curBlock->setEnterPos(bline->getYpos() - curBlock->getYpos());
		curBlock->setHighlight();
		isPress = true;
    }
}

//键盘按下事件处理（过滤掉自动重复事件)
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
        case Qt::Key_Space: pause();break;//press space to pause
		default: gameover();break;
        }

	}
	else if(alive&&event->key()==Qt::Key_Space) 
        resume();//press space to resume
}

//键盘松开事件处理
void GameController::handleKeyUp(QKeyEvent *event)
{
	if(!isPause&&alive&&event->key()!=Qt::Key_Space)
	{
	    curBlock->setExitPos(bline->getYpos() - curBlock->getYpos());
		double add = curBlock->calScore(curBlock->getEnterPos(),curBlock->getExitPos());
		
		//显示得分反馈
		if(add<30)
		    animationStart(1);//good
		else if(add<70)
			animationStart(2);//cool
		else
			animationStart(3);//excellent
        totalScore += curBlock->calScore(curBlock->getEnterPos(),curBlock->getExitPos());
        scBox->setScore(totalScore);
	}	
}

//得分反馈显示
void GameController::animationStart(int i)
{
	if(scene.items().indexOf(mymark)!=-1)
		scene.removeItem(mymark);
	atimer = new QTimeLine(500);
    atimer->setFrameRange(0, 100);
	mymark = new animationMark(i);
    animation = new QGraphicsItemAnimation;
    animation->setItem(mymark);
    animation->setTimeLine(atimer);
	for(int i=0;i<200;i++)
		animation->setPosAt(i/200.0,QPointF(100,-150+0.3*i));    
	scene.addItem(mymark);
    atimer->start();
}

//更新视图中的数据
void GameController::redirect()
{

	//添加block
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

	//移除block
	if(curBlock->getYpos()>0)
	{
		scene.removeItem(curBlock);
		Block *w = allBlocks.takeFirst();
		delete w;
		w = NULL;
		if(!allBlocks.isEmpty())
        {
		    curBlock = allBlocks.first();
        }
		else 
		{
			curBlock = NULL;
		}

		//升级更改速度
		foreach(Block* w,allBlocks)
		{
			if(totalScore>1000) w->levelup(3);
			else if(totalScore>500) w->levelup(2);
			else if(totalScore>200) w->levelup(1);
		}
	}
}

//事件过滤器
bool GameController::eventFilter(QObject *object, QEvent *event)
{
	if(event->type() == QEvent::KeyPress)
    {
        handleKeyDown((QKeyEvent*)event);
		isPress = true;
        return true;
    }
    else if(event->type() == QEvent::KeyRelease&&(!((QKeyEvent*)event)->isAutoRepeat())&&(isPress))
	{
		handleKeyUp((QKeyEvent*)event);
		isPress = false;
        return true;
    }
	else if(allBlocks.isEmpty()&&alive&&(!isPause))
	{
		gameover();
		return false;
	}

    else 
    {
        return false;
    }
}

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