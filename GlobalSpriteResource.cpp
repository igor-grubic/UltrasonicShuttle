#include "GlobalSpriteResource.h"

GlobalSpriteResource::GlobalSpriteResource() {
    sprites = new Sprite*[NUM_SPRITES];
}

GlobalSpriteResource::~GlobalSpriteResource() {
    freemem();
}

void GlobalSpriteResource::set(int num, Sprite* sprite) {
     sprites[num] = sprite;
}

void GlobalSpriteResource::set(int num, string file, int frames, int animations) {
     sprites[num] = new Sprite(file, frames, animations);
    if (!sprites[num]->isSprite()) {
        cout << "Unable to load bitmap: " << SDL_GetError() << endl;
    } else {
        sprites[num]->setTransparency(255, 0, 255);
        cout << "loaded sprite" << endl;
    }
}

Sprite* GlobalSpriteResource::get(int num) {
    if(num >= 0 && num < NUM_SPRITES) {
        return sprites[num];
    }
    return NULL;
}


void GlobalSpriteResource::draw(SDL_Surface* screen, int num,  int x, int y) {
    sprites[num]->draw(screen, x, y);
}


void GlobalSpriteResource::freemem() {
    for(int i = 0; i < NUM_SPRITES; i++) {
        if(sprites[i]->isSprite() != NULL) {
            SDL_free(sprites[i]->getSurface());
        }
    }
}
