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
private:
	void initScene();
	void initSceneBackground();
	QGraphicsScene *scene;
	QGraphicsView *view;
	GameController *game;
};


#endif