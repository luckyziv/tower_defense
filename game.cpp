#include "game.h"
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include "global.h"
#include "monster.h"

#define X40(num)    (((num) - 1) * 40 + 10)

/*
 * @pathNum: use whitch path - 0, 1
 * @staCoorNum: every path coor points count
 * @monster id: m id
 */
#define insertOneMonster(pathNum, staCoorNum, monsterId)   \
monsterVec.push_back(new Monster(wayPointsArr[pathNum], pathLength[pathNum], X40(staco[staCoorNum].x), X40(staco[staCoorNum].y), monsterId));


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

    // This timer do update monsters, 1 monster/2s
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
                new coorStr(X40(19), X40(9))
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
                new coorStr(X40(8), X40(13))
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


    // monster move
    QTimer *timer1 = new QTimer(this);
    timer1->start(120);
    connect(timer1, &QTimer::timeout, [=]() {
        // monsterVec.begin(): return the 1st argument memory address
        for (auto monster = monsterVec.begin(); monsterVec.end(); monster++){
            (*monster)->move();
        }

    });

    update();   // important

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
}

void game::drawMapArr(QPainter &painter)
{
    int Map_1[16][26] = {
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 2, 8, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 8, 8, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 8, 0, 0, 2, 8, 1, 1, 2, 8, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 8, 8, 0, 0, 8, 8, 1, 1, 8, 8, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 0, 2, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 0, 8, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 2, 8, 0, 0, 0, 0, 2, 8, 0, 0, 0, 0, 2, 8, 0, 0, 0, 1, 1, 1, 1, 9, 8,
        0, 1, 1, 8, 8, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 8, 8, 0, 0, 0, 1, 1, 1, 1, 8, 8,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
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
            case 0:
                painter.drawPixmap(j * 40, i * 40, 40, 40,
                                   QPixmap(":/new/prefix1/image/草地块.png"));
                break;
            case 1:
                painter.drawPixmap(j * 40, i * 40, 40, 40,
                                   QPixmap(":/new/prefix1/image/地面.png"));
                break;
            case 2:
                painter.drawPixmap(j * 40, i * 40, 80, 80,
                                   QPixmap(":/new/prefix1/image/石砖块.png"));
                break;
            case 9:
                painter.drawPixmap(j * 40, i * 40, 80, 80,
                                   QPixmap(":/new/prefix1/image/房子.png"));
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

// insert monster
void game::getNewMonsterAndPathInfo(coorStr **wayPointArr1, coorStr **wayPointArr2, coorStr *staco, int *pathLength, QLabel *victoryLable)
{
    coorStr **wayPointsArr[] = {wayPointArr1, wayPointArr2};   // two path points

    if ((monsterCounter >= 1) && (monsterCounter <= 14)) {
        insertOneMonster(0, 0, 1);
    } else if ((monsterCounter >= 14) && ( monsterCounter < 28)) {

    }



    monsterCounter++;
}
