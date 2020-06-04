#ifndef MONSTER_H
#define MONSTER_H

#include <QVector>
#include <QString>
#include <QPixmap>

#include "global.h"

class Monster
{

private:
    int monsterX;
    int monsterY;
    int monsterId;
    int monsterHealth;
    int monsterWidth;
    int monsterHeight;
    int monsterSpeed = 10;

    QString imgPath;
    QVector<coorStr *> pathPointsArr;  // path points

public:
    Monster(coorStr **pointArr, int arrLength, int x, int y, int mid);
    ~Monster();

    int getX(void) const;
    int getY(void) const;
    int getWidth(void) const;
    int getHeight(void) const;
    QString getImgPath(void) const;
    bool move(void);
};

#endif // MONSTER_H
