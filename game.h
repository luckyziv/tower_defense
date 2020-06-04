#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QPainter>
#include <QLabel>
#include "global.h"
#include "monster.h"

class game : public QMainWindow
{
    Q_OBJECT
public:
    explicit game(int level);
    ~game(void);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QVector<coorStr *> wayPoint;
    QVector<Monster *> monsterVec;


    void drawMapArr(QPainter &painter);
    void drawMonster(QPainter &painter);
    void getNewMonsterAndPathInfo(coorStr **wayPointArr1, coorStr **wayPointArr2,
                          coorStr *staco, int *pathLength, QLabel *victoryLable);
    int levelNumber;
    int monsterCounter;


signals:

public slots:

};

#endif // GAME_H
