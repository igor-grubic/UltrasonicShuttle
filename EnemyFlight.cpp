#include "EnemyFlight.h"

EnemyFlight::EnemyFlight() {

}

EnemyFlight::~EnemyFlight() {

}

void EnemyFlight::process(Enemy &enemy) {
    if(enemy.flightType == ENEMY_FLIGHT_NORMAL) {
        enemy.y += enemy.speedY;
        enemy.x += enemy.speedX;
    } else if(enemy.flightType == ENEMY_FLIGHT_SINE) {
        int origX = enemy.x;
        enemy.x = origX + 20*sin(enemy.y*1.8);
        enemy.y += enemy.speedY;
    }
}
