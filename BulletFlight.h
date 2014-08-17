
#ifndef __BULLET_FLIGHT_H__
#define __BULLET_FLIGHT_H__

#include "common.h"
#include "Bullet.h"

using namespace std;

enum {
    BULLET_FLIGHT_NORMAL,
    BULLET_FLIGHT_SINE
};

class BulletFlight {
public:
    BulletFlight();
    ~BulletFlight();
    static void process(Bullet &bullet);

};
#endif

