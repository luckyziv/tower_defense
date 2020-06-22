#include "selectbox.h"
#include <QDebug>

//QString imgPath = ":/new/prefix/image/select_base.png"
SelectBox::SelectBox(QString imgPath):
    selectImgPath(imgPath)
{
    qDebug() << "select box init!";
    setFlag = false;
}

int SelectBox::getX() const
{
   return selectX;
}

int SelectBox::getY() const
{
   return selectY;
}

int SelectBox::getWidth() const
{
   return selectWidth;
}

int SelectBox::getHeight() const
{
   return selectHeight;
}

QString SelectBox::getImgPaht() const
{
    return selectImgPath;
}

void SelectBox::settingFlag(bool flag)
{
    setFlag = flag;
}

bool SelectBox::getSettingFlag()
{
    return setFlag;
}

void SelectBox::setBoxAndSubPos(int x, int y)
{
    selectX = x - 80;
    selectY = y - 75;
    selectWidth = 240;
    selectHeight = 240;

    subBox[0].x = x + 10;
    subBox[0].y = y - 70;
    subBox[0].imgPath = ":/new/prefix1/image/arms1.png";

    subBox[1].x = selectX + 30;
    subBox[1].y = selectY + 60;
    subBox[1].imgPath = ":/new/prefix1/image/arms2.png";

    subBox[2].x = x + 10;
    subBox[2].y = y + 80;
    subBox[2].imgPath = ":/new/prefix1/image/buy_fire.png";

    subBox[3].x = selectX + 120;
    subBox[3].y = selectY + 60;
    subBox[3].imgPath = ":/new/prefix1/image/buy_green.png";

    setFlag = true;
}
