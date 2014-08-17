#include "Bullet.h"

Bullet::Bullet()  {
    this->exists = 0;
}


Bullet::~Bullet() {

}

void Bullet::draw(SDL_Surface* screen, int x, int y) {
    image->animate();
    image->draw(screen, x, y);
}
