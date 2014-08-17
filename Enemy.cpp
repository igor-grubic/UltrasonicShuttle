#include "Enemy.h"

Enemy::Enemy() {
    this->exists = 0;
}

Enemy::~Enemy() {

}

void Enemy::draw(SDL_Surface* screen, int x, int y) {
    image->animate();
    image->draw(screen, x, y);
}
