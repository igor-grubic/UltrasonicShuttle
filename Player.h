#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "common.h"
#include "Bullet.h"


using namespace std;

class Player {
public:
    Player();
    ~Player();
    void draw(SDL_Surface* screen, int x, int y);
    void addBullet(Sprite* beam, int x, int y, int speedX, int speedY, int targetX, int targetY, int damage, int flightType);
    int getEmptyBullet();
    float x;
    float y;
    int armor;
    int speed;
    Sprite* image;

    int beam;
    long lastShot;
    int shotDelay;

    Bullet bullets[MAX_BULLETS];
};
#endif
