#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "common.h"

using namespace std;

class Explosion {
public:
    Explosion();
    ~Explosion();
    void draw(SDL_Surface* screen, int x, int y);

    bool exists;
    int x;
    int y;

    int startTime;
    int duration;
    Sprite* image;
};
#endif

