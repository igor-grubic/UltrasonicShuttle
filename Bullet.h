#ifndef __BULLET_H__
#define __BULLET_H__

#include "common.h"

using namespace std;

class Bullet {
public:
    Bullet();
    ~Bullet();
    void draw(SDL_Surface* screen, int x, int y);

    bool exists;
    int x;
    int y;
    int speedX;
    int speedY;
    int targetX;
    int targetY;
    float angle;
    int damage;
    int flightType;


    Sprite* image;
};
#endif
