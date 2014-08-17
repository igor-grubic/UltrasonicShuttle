#include "BulletFlight.h"
#include <tgmath.h>

BulletFlight::BulletFlight() {

}

BulletFlight::~BulletFlight() {

}

void BulletFlight::process(Bullet &bullet) {
    if(bullet.flightType == BULLET_FLIGHT_NORMAL) {
      //float x = bullet.x + 2 * cos(bullet.angle);
      //float y = bullet.y + 2* sin(bullet.angle);
        bullet.x;
        bullet.y -= 10;
        //mouse collision

    } else if(bullet.flightType == BULLET_FLIGHT_SINE) {
        int origX = bullet.x;
        bullet.x = origX + 20*sin(bullet.y*1.8);
        bullet.y += bullet.speedY;
    }
}
