#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <qtimer.h>

class GameController:public QObject
{
    Q_OBJECT
public:
    GameController(QGraphicsScene &scene, QObject *parent = 0);
    ~GameController();
    void blockEnterline();
    void blockExitline();
private slots:
    void pause();
    void resume();
    void gameover();
protected:
    bool eventFilter(QObject *object, QEvent *event);
private:
    void handleKeyDown(QEvent *event);
    void handleKeyUp(QEvent *event);
    void blockDrop();
    QTimer timer;
    QGraphicsScene &scene;
    Block *curBlock;
    bool isPause;
};
#endif