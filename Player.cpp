#include "Player.h"
#include <tgmath.h>


Player::Player() {
    for(int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].exists = false;
    }
}

Player::~Player() {
    // free loaded bitmap
    if(image != NULL) {
        SDL_FreeSurface(image->getSurface());
    }
}


void Player::draw(SDL_Surface* screen, int x, int y) {
    image->animate();
    image->draw(screen, x, y);
}

void Player::addBullet(Sprite* beam, int x, int y, int speedX, int speedY, int targetX, int targetY, int damage, int flightType) {
    int i = getEmptyBullet();
    if(i != -1) {
        //   cout << "Add bullet to index " << i << endl;
        bullets[i].exists = true;
        bullets[i].image = beam;
        bullets[i].x = x;
        bullets[i].y = y;
        bullets[i].speedY = speedY;
        bullets[i].speedX = speedX;
        bullets[i].targetX = targetX;
        bullets[i].targetY = targetY;
        int deltaX = targetX - x;
        int deltaY = targetY - y;
        bullets[i].angle = atan2(deltaY, deltaX);
        bullets[i].damage = damage;
        bullets[i].flightType = flightType;
    }
}


int Player::getEmptyBullet() {
    for(int i = 0; i < MAX_BULLETS; i++) {
        if(!bullets[i].exists) {
            return i;
        }
    }
    return -1;
}
