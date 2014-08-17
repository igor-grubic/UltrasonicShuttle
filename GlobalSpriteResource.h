#ifndef __GLOBALSPRITERESOURCE_H__
#define __GLOBALSPRITERESOURCE_H__

#include "common.h"


#define NUM_SPRITES 50

using namespace std;

class GlobalSpriteResource {
public:
    GlobalSpriteResource();
    ~GlobalSpriteResource();

    Sprite* get(int num);
    void set(int num, Sprite* sprite);
    void set(int num, string file, int frames, int speed);

    void draw(SDL_Surface* screen, int num,  int x, int y);
    void freemem();

    Sprite** sprites;
};
#endif

