
#ifndef __ENEMY_FLIGHT_H__
#define __ENEMY_FLIGHT_H__

#include "common.h"
#include "Enemy.h"

using namespace std;

enum {
    ENEMY_FLIGHT_NORMAL,
    ENEMY_FLIGHT_SINE
};

class EnemyFlight {
public:
    EnemyFlight();
    ~EnemyFlight();
    static void process(Enemy &enemy);

};
#endif


