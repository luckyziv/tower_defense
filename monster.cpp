#include "monster.h"
#include <QDebug>

Monster::Monster(coorStr **pointArr, int arrLength, int x, int y, int mid):
    monsterX(x), monsterY(y), monsterId(mid)
{
    qDebug() << "new Monster!";
    for (int i = 0; i < arrLength; i++) {
        pathPointsArr.push_back(pointArr[i]);
    }

    switch (mid) {
    case 0:
        monsterHealth = 100;
        monsterWidth = 64;
        monsterHeight = 64;
        imgPath = ":/new/prefix1/image/monster1.png";

        break;
    case 1:
        break;
    default:
        break;
    }
}

Monster::~Monster()
{

}

int Monster::getX() const
{
    return monsterX;
}

int Monster::getY() const
{
    return monsterY;
}

int Monster::getWidth() const
{
    return monsterWidth;
}

int Monster::getHeight() const
{
    return monsterHeight;
}

QString Monster::getImgPath() const
{
    return imgPath;
}

bool Monster::move()
{
    if (pathPointsArr.isEmpty())
        return false;

    // down
    if (pathPointsArr.at(0)->y > monsterY){
        monsterY += monsterSpeed;
        return true;
    }

    // left
    if (pathPointsArr.at(0)->x < monsterX) {
        monsterX -= monsterSpeed;
        return true;
    }

    // right
    if (pathPointsArr.at(0)->x > monsterX) {
        monsterX += monsterSpeed;
        return true;
    }

    // up
    if (pathPointsArr.at(0)->y < monsterY){
        monsterY -= monsterSpeed;
        return true;
    }

    if ((pathPointsArr.at(0)->x == monsterX) || (pathPointsArr.at(0)->y == monsterY)) {
        pathPointsArr.erase(pathPointsArr.begin());

        // if monster arrive home, let it hide by home.png
        if (pathPointsArr.isEmpty()) {
            imgPath = ":/image/home.png";
        }

        return true;
    }
}

