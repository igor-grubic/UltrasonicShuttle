#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "common.h"

using namespace std;


class Enemy {
public:
    Enemy();
    ~Enemy();
    void draw(SDL_Surface* screen, int x, int y);

    bool exists;
    int x;
    int y;
    int speedX;
    int speedY;

    int damage;
    int shotDelay;
    int lastShot;

    int beam;
    int armor;
    int flightType;

    Sprite* image;
};
#endif

