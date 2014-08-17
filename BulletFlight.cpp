#include "BulletFlight.h"
#include <tgmath.h>

BulletFlight::BulletFlight() {

}

BulletFlight::~BulletFlight() {

}

void BulletFlight::process(Bullet &bullet) {
    if(bullet.flightType == BULLET_FLIGHT_NORMAL) {
      //  cout << "Bullet Y, Bullet Speed " << bullet.y << " " << bullet.speed << endl;
      //float x = bullet.x + 2 * cos(bullet.angle);
      //float y = bullet.y + 2* sin(bullet.angle);
        bullet.x;
        bullet.y -= 10;

        if(//bullet.x > bullet.targetX -10 && bullet.x < bullet.targetX +10 &&
           bullet.y > bullet.targetY -10 && bullet.y < bullet.targetY +10)
            bullet.exists = false;
        //bullet.x -= m;
        //bullet.y = bullet.x * m;
        //bullet.y += bullet.speedY;
        //bullet.x += bullet.speedX;
     //   cout << "Bullet Y new " << bullet.y << endl;
    } else if(bullet.flightType == BULLET_FLIGHT_SINE) {
      //  cout << "Bullet Y, Bullet Speed " << bullet.y << " " << bullet.speed << endl;
        int origX = bullet.x;
        bullet.x = origX + 20*sin(bullet.y*1.8);
        bullet.y += bullet.speedY;
     //   cout << "Bullet Y new " << bullet.y << endl;
    }
}
