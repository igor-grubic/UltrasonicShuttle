#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "common.h"


#define LVL_ENEMY   'E'
#define LVL_BOSS    'B'
#define LVL_BEGIN   'S'
#define LVL_END     'F'

using namespace std;

struct Command {
    long timer;
    char cmd;
    int p1;
    int p2;
    int p3;
    int p4;
    int p5;
    int p6;
    int p7;
    int p8;
    int p9;
    int p10;
};

class Level {
public:
    Level();
    ~Level();


    void loadLevel(int level);
    void addEnemyToQueue(int timer, int image, int posX, int posY, int shotDelay, int damage, int armor, int beam, int flightType, int speedX, int speedY);

    bool isNextEvent();
    Command* nextEvent();

    int level;

    int levelY;
    int levelScrollSpeed;

    int backgroundImage;
    int backgroundScrollSpeed;

    long levelStartTime;

    vector<Command*> lvl_cmds;
};
#endif

