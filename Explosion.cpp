#include "Explosion.h"

Explosion::Explosion() {
    this->exists = false;
}

Explosion::~Explosion() {

}

void Explosion::draw(SDL_Surface* screen, int x, int y) {
    image->animate();
    image->draw(screen, x, y);
}

