#include <qgraphicsview.h>
#include <qtimer.h>
#include "MainWindow.h"
#include "GameController.h"
//need to write GameController
MainWindow::MainWindow(QWidget* parent):QMainWindow(parent),scene(new QGraphicsScene(this)),view(new QGraphicsView(scene,this)),game(new GameController(*scene, this))
{
    setCentralWidget(view);
	setFixedSize(200,2000);
 
    initScene();
    initSceneBackground();
 
    QTimer::singleShot(0, this, SLOT(adjustSize()));
};

MainWindow::~MainWindow()
{

}

void MainWindow::adjustSize()
{
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}

void MainWindow::initScene()
{
    scene->setSceneRect(0, -1000, 200, 2000);
}

void MainWindow::initSceneBackground()
{
    QPixmap bg(200, 200);
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::gray));
    p.drawRect(0, 0, 200, 200);

    view->setBackgroundBrush(QBrush(bg));
}