#include <qgraphicsview.h>
#include <qtimer.h>
#include "MainWindow.h"
#include "GameController.h"
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget* parent):QMainWindow(parent),scene(new QGraphicsScene(this)),view(new QGraphicsView(scene,this)),game(new GameController(*scene, this))
{
    setCentralWidget(view);
	resize(600,800);
	setVisible(false);

    createActions();
    createMenus();
 
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
    scene->setSceneRect(0, -300, 200, 400);
}

//´°¿Ú±³¾°
void MainWindow::initSceneBackground()
{
	this->setObjectName("window");
	view->setStyleSheet("border-image:url(:/images/milkyway1.png);");
}

//¹¤¾ßÀ¸
void MainWindow::createActions()
{
    level1Action = new QAction(tr("&level 1"),this);
    level1Action->setWhatsThis(tr("&Ð¡ÐÇÐÇ"));
	connect(level1Action,&QAction::triggered,game,&GameController::level1);

    level2Action = new QAction(tr("&level 2"),this);
    level2Action->setWhatsThis(tr("&Ð£¸è"));
    connect(level2Action,&QAction::triggered,game,&GameController::level2);

    level3Action = new QAction(tr("&level 3"),this);
    level3Action->setWhatsThis(tr("&Ò°·ä·ÉÎè"));
    connect(level3Action,&QAction::triggered,game,&GameController::level3);

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the game"));
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    pauseAction = new QAction(tr("&Pause"), this);
    pauseAction->setStatusTip(tr("Pause..."));
    connect(pauseAction, &QAction::triggered, game, &GameController::pause);

    resumeAction = new QAction(tr("&Resume"), this);
    resumeAction->setStatusTip(tr("Resume..."));
    connect(resumeAction, &QAction::triggered, game, &GameController::resume);

    gameHelpAction = new QAction(tr("Game &Help"), this);
    gameHelpAction->setShortcut(tr("Ctrl+H"));
    gameHelpAction->setStatusTip(tr("Help on this game"));
    connect(gameHelpAction, &QAction::triggered, this, &MainWindow::gameHelp);

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's about box"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, &QAction::triggered, qApp, QApplication::aboutQt);
}

void MainWindow::createMenus()
{
    QMenu *newGame = menuBar()->addMenu(tr("&New Game"));
    newGame->addAction(level1Action);
    newGame->addSeparator();
    newGame->addAction(level2Action);
    newGame->addSeparator();
    newGame->addAction(level3Action);

    QMenu *options = menuBar()->addMenu(tr("&Options"));
    options->addAction(pauseAction);
    options->addAction(resumeAction);
    options->addSeparator();
    options->addAction(exitAction);

    QMenu *help = menuBar()->addMenu(tr("&Help"));
    help->addAction(gameHelpAction);
    help->addAction(aboutAction);
    help->addAction(aboutQtAction);
}

void MainWindow::gameHelp()
{
	QMessageBox msbox;
	msbox.setText("Press keys 1,2,3,4 to hit the blocks when the blocks intersect the base line.\nPress space to pause or continue.");
	msbox.exec();
}

void MainWindow::about()
{
	QMessageBox msbox;
	msbox.setText("This is a small Qt application.");
	msbox.exec();
}