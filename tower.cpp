#include "tower.h"

Tower::Tower(int x, int y, int width = 80, int height = 80)
    : towerX(x), towerY(y), towerWidth(width), towerHeight(height)
{
    // TODO:
    towerPath = ":/new/prefix1/image/tower1.png";
}

int Tower::getX() const
{
    return towerX;
}

int Tower::getY() const
{
    return towerY;
}

int Tower::getWidth() const
{
    return towerWidth;
}

int Tower::getHeight() const
{
    return towerHeight;
}

QString Tower::getTowerImgPath() const
{
    return towerPath;
}
