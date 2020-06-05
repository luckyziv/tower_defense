#ifndef TOWER_H
#define TOWER_H

#include <QString>

class Tower
{
private:
    int towerX;
    int towerY;
    int towerWidth;
    int towerHeight;
    QString towerPath;

public:
    Tower(int x, int y, int width, int height);
    int getX(void) const;
    int getY(void) const;
    int getWidth(void) const;
    int getHeight(void) const;
    QString getTowerImgPath(void) const;
};

#endif // TOWER_H
