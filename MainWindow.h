#ifndef RHYTHMMATER_H
#define RHYTHMMATER_H

#include <QtWidgets/QMainWindow>
#include <qgraphicsitem.h>
#include <qtimer.h>
#include "ui_rhythmmater.h"

class GameController;
class QKeyEvent;
class QTimer;
class MainWindow: public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void adjustSize();
	void gameHelp();
	void about();

private:
	void initScene();
	void initSceneBackground();
    void createActions();
    void createMenus();

    QAction *level1Action;
    QAction *level2Action;
    QAction *level3Action;
	QAction *exitAction;
	QAction *pauseAction;
	QAction *resumeAction;
	QAction *gameHelpAction;
	QAction *aboutAction;
	QAction *aboutQtAction;

	QGraphicsScene *scene;
	QGraphicsView *view;
	GameController *game;
};


#endif