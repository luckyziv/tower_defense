#include "game.h"
#include <QDebug>
#include <QLabel>
#include <QTimer>

#include "global.h"
#include "monster.h"
#include "tower.h"

#define X40(num)    (((num) - 1) * 40 + 10)

/*
 * @pathNum: use whitch path - 0, 1
 * @staCoorNum: every path coor points count
 * @monster id: m id
 */
#define insertOneMonster(pathNum, staCoorNum, monsterId)   \
monsterVec.push_back(new Monster(wayPointsArr[pathNum], pathLength[pathNum], X40(staco[staCoorNum].x), X40(staco[staCoorNum].y), monsterId));

// must X/Y
#define mouseClickIsInRegion(X, width, Y, height)   \
((event->x() >= (X)) && (event->x() <= ((X) + (width)))) &&   \
((event->y() >= (Y)) && (event->y() <= ((Y) + (height))))

game::game(int level)
{
    qDebug() << "level: " << level;

    // 1040/40 = 26 
    // 640 /40 = 16
    setFixedSize(1040, 640);
    setWindowTitle("Game Window");

    levelNumber = level;
    monsterCounter = 0;

    QLabel *victoryNote = new QLabel(this);
    victoryNote->move(176, 180);
    victoryNote->setFont(QFont("楷体", 110));
    victoryNote->setText(QString("游戏胜利！"));
    victoryNote->hide();

    selectBox = new SelectBox(":/new/prefix1/image/select_box.png");

    // timer: add monsters, 1 monster/2s
    QTimer *timer = new QTimer(this);
    timer->start(2000);
    connect(timer, &QTimer::timeout, [=]() {
        qDebug() << "timer running! level:" << level;

        switch (level) {
        case 0: {
            // path points array
            coorStr *wayPointArr1[] = {
                new coorStr(X40(8), X40(6)),
                new coorStr(X40(2), X40(6)),
                new coorStr(X40(2), X40(13)),
                new coorStr(X40(19), X40(13)),
                new coorStr(X40(19), X40(9)),

                new coorStr(X40(26), X40(9))    // home
            };
            coorStr *wayPointArr2[] = {
                new coorStr(X40(20), X40(6)),
                new coorStr(X40(14), X40(6)),
                new coorStr(X40(14), X40(13)),
                new coorStr(X40(8), X40(13)),
                new coorStr(X40(2), X40(9)),
                new coorStr(X40(20), X40(6)),
                new coorStr(X40(14), X40(6)),
                new coorStr(X40(14), X40(13)),
                new coorStr(X40(8), X40(13)),

                new coorStr(X40(26), X40(9))    // home
            };

            // path monster start point
            coorStr staco[] = {coorStr(8, 0), coorStr(20, 0), coorStr(8, -1), coorStr(20, -1)};
            // every path points num
            int pathLength[] = {sizeof(wayPointArr1)/sizeof(coorStr*),
                               sizeof(wayPointArr1)/sizeof(coorStr*)};

            getNewMonsterAndPathInfo(wayPointArr1, wayPointArr2, staco, pathLength, victoryNote);   // add a monster every 2s ==> new a monster
            break;
        }
        case 1:
            //TODO:
            break;
        default:
            break;
        };
    });
    // add monsters end

    // monster move
    QTimer *timer1 = new QTimer(this);
    timer1->start(120);
    connect(timer1, &QTimer::timeout, [=]() {
        //qDebug() << "timer1";
        // monsterVec.begin(): return the 1st argument memory address
        for (auto monster = monsterVec.begin(); monster != monsterVec.end(); monster++){
            (*monster)->move();
            update();
        }

    });
    // monster move end

}

game::~game()
{

}

void game::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 设置抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);

    // draw map
    drawMapArr(painter);
    // draw monster
    drawMonster(painter);
    // draw tower
    drawSelectBox(painter);
}

void game::mousePressEvent(QMouseEvent *event)
{
//  qDebug() << "mouse press coordinate: " << event->x() << event->y();
    for (auto towerbase = towerPosVec.begin(); towerbase != towerPosVec.end(); towerbase++) {
        if (mouseClickIsInRegion((*towerbase)->getX(), (*towerbase)->getWidth(), (*towerbase)->getY(), (*towerbase)->getHeight())) {
            qDebug() << "mouse click in region: " << (*towerbase)->getX() << (*towerbase)->getY();
            selectBox->setBoxAndSubPos((*towerbase)->getX(), (*towerbase)->getY());
            update();   //to draw selectBox
        }
    }
}

void game::drawMapArr(QPainter &painter)
{
    int Map_1[16][26] = {
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 3, 6, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 6, 1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 6, 6, 1, 1, 3, 6, 0, 0, 0,
        0, 0, 0, 0, 0, 6, 6, 1, 1, 6, 6, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 3, 6, 0, 1, 1, 0, 0, 0, 0, 3, 6, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 3, 6, 0, 1, 1, 0, 6, 6, 0, 1, 1, 0, 3, 6, 0, 6, 6, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 6, 6, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 6, 6, 1, 1, 1, 1, 1, 1, 5, 6,
        0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 6, 6,
        0, 1, 1, 0, 3, 6, 0, 0, 3, 6, 0, 0, 3, 6, 0, 0, 3, 6, 1, 1, 3, 6, 0, 0, 0, 0,
        0, 1, 1, 0, 6, 6, 0, 0, 6, 6, 0, 0, 6, 6, 0, 0, 6, 6, 1, 1, 6, 6, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    int Map_2[16][26] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    int Map_3[16][26] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    int Map[16][26];
    switch (levelNumber) {
    case 0:
        memcpy(Map, Map_1, sizeof(Map));
        break;
    case 1:
        memcpy(Map, Map_2, sizeof(Map));
        break;
    case 2:
        memcpy(Map, Map_3, sizeof(Map));
        break;
    default:
        break;
    }

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 26; j++) {
            switch (Map[i][j]) {
            case 0: // grass
                painter.drawPixmap(j * 40, i * 40, 40, 40,
                                   QPixmap(":/new/prefix1/image/grass_block.png"));
                break;
            case 1: // monster path
                painter.drawPixmap(j * 40, i * 40, 40, 40,
                                   QPixmap(":/new/prefix1/image/path_block.png"));
                break;
            case 3: // tower position
                painter.drawPixmap(j * 40, i * 40, 80, 80,
                                   QPixmap(":/new/prefix1/image/tower_block.png"));
                towerPosVec.push_back(new Tower(j * 40, i * 40, 80, 80));  // record base of defense tower
                break;
            case 5: // home
                painter.drawPixmap(j * 40, i * 40, 80, 80,
                                   QPixmap(":/new/prefix1/image/home.png"));
                break;
            default:
                break;
            };
        }
    }
}

void game::drawMonster(QPainter &painter)
{
    for (auto moni : monsterVec)
        painter.drawPixmap(moni->getX(), moni->getY(), moni->getWidth(), moni->getHeight(), QPixmap(moni->getImgPath()));

}

void game::drawSelectBox(QPainter &painter)
{
    qDebug() << "draw select box!";
    painter.drawPixmap(selectBox->getX(), selectBox->getY(), \
                       selectBox->getWidth(), selectBox->getHeight(), QPixmap(selectBox->getImgPaht()));

    for (int i = 0; i < 4; i++) {
        painter.drawPixmap(selectBox->subBox[i].x, selectBox->subBox[i].y, \
                           selectBox->subBox[i].width, selectBox->subBox[i].height, QPixmap(selectBox->subBox[i].imgPath));
    }
}

// insert monster
void game::getNewMonsterAndPathInfo(coorStr **wayPointArr1, coorStr **wayPointArr2, coorStr *staco, int *pathLength, QLabel *victoryLable)
{
    coorStr **wayPointsArr[] = {wayPointArr1, wayPointArr2};   // two path points

    if ((monsterCounter >= 1) && (monsterCounter <= 14)) {
        insertOneMonster(0, 0, 0);
    } else if ((monsterCounter >= 14) && ( monsterCounter < 28)) {

    }

    monsterCounter++;
}
