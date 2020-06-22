#ifndef SELECTBOX_H
#define SELECTBOX_H
#include <QString>

typedef struct {
    int x;
    int y;
    int width = 56;
    int height = 56;
    QString imgPath;
}subBoxInfo;

class SelectBox
{
public:
    SelectBox(QString imgPath);
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    QString getImgPaht() const;

    void settingFlag(bool flag);
    bool getSettingFlag(void);
    void setBoxAndSubPos(int x, int y);

    subBoxInfo subBox[4];
private:
    int selectX;
    int selectY;
    int selectWidth;
    int selectHeight;
    bool setFlag;

    QString selectImgPath;

};

#endif // SELECTBOX_H
