#include <qgraphicsview.h>
#include <qtimer.h>
#include "MainWindow.h"
//need to write GameController
MainWindow::MainWindow(QWidget* parent):QMainWindow(parent),scene(new QGraphicsScene(this)),view(new QGraphicsView(scene,this)),game(new GameController(*scene, this))
{
    setCentralWidget(view);
    resize(600, 600);
 
    initScene();
    initSceneBackground();
 
    QTimer::singleShot(0, this, SLOT(adjustViewSize()));
};