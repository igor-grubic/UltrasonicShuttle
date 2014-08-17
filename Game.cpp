#include "Game.h"

Game::Game() {

}

Game::~Game() {

}

int Game::init() {

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    screen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
    if ( !screen ) {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    SDL_EnableKeyRepeat(0,0);

    gsr = new GlobalSpriteResource();
    gsr->set(SR_SHIP_1, "sprites/spaceship.bmp", 1, 0);
    gsr->set(SR_BEAM_1, "sprites/beam_1.bmp", 2, 100);
    gsr->set(SR_BEAM_2, "sprites/beam_2.bmp", 1, 0);
    gsr->set(SR_BACKGROUND_1, "sprites/back_1.bmp", 1, 0);
    gsr->set(SR_BACKGROUND_2, "sprites/back_2.bmp", 1, 0);
    gsr->set(SR_ENEMY_1, "sprites/enemy_1.bmp",6,75);
    gsr->set(SR_EXPLOSION_1, "sprites/explosion_1.bmp",8,25);

    bf = new BulletFlight();
    ef = new EnemyFlight();

    player = new Player();

    reset();
//    SDL_TimerID bullet_timer = SDL_AddTimer(100, &handleBullets, void);

    return 0;
}

void Game::reset() {
    //setting sdl keys to false(322?)
    memset(KEYS,false,322);
    for(int i = 0; i < 323; i++) {
        KEYS[i] = false;
    }

    player->image = gsr->get(SR_SHIP_1);
    player->x = 320;
    player->y = 440;
    player->armor = 1;
    player->speed = 8;
    player->beam = PLAYER_BEAM_NORMAL;
    player->lastShot = SDL_GetTicks();
    player->shotDelay = 350;

    level = new Level();
 //   level->loadLevel("levels/1.lvl");
    level->loadLevel(1);
    level->levelY = 0;
    level->levelScrollSpeed = 2;
    level->backgroundImage = SR_BACKGROUND_2;

    level->levelStartTime = SDL_GetTicks();
}

void Game::run() {
    //inputs
    //ultrasonicsensor()

    handleInput();

    //automatic shooting
    if(SDL_GetTicks() - player->lastShot > player->shotDelay) {
            shootbeam(player->beam);
    }

    // clear screen
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    backGround();

    handleEnemies();
    handleBullets();
    handleExplosions();

    handleLevel();

    player->draw(screen, player->x, player->y);

    // finally, update the screen :)
    SDL_Flip(screen);

}

void Game::handleInput() {

    readInputEvent();

    if(KEYS[SDLK_LEFT]) {
        if(player->x - player->speed >= 0) {
            player->x -= player->speed;
        }
    }
    if(KEYS[SDLK_RIGHT]) {
        if(player->x + player->speed <= screen->w) {
            player->x += player->speed;
        }
    }
    /*
    if(KEYS[SDLK_UP]) {
        if(player->y - player->speed >= 0) {
            player->y -= player->speed;
        }
    }
    if(KEYS[SDLK_DOWN]) {
        if(player->y + player->speed <= screen->h) {
            player->y += player->speed;
        }
    }*/
    if(KEYS[SDLK_s]) {
        if(SDL_GetTicks() - player->lastShot > player->shotDelay) {
            shootbeam(player->beam);
        }
    }
    if(KEYS[SDLK_q]) {
        if(player->beam == PLAYER_BEAM_CHARGE) {
            player->beam = PLAYER_BEAM_NORMAL;
        } else {
            player->beam = PLAYER_BEAM_CHARGE;
        }
    }
    if(KEYS[SDLK_r]) {
        reset();
    }

    if(KEYS[SDLK_ESCAPE]) {
        gs = GS_DONE;
    }
}

void Game::readInputEvent() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_MOUSEMOTION:
                //SDL_PixelFormat* fmt = screen->format;
                mouseX = event.motion.x;
                mouseY = event.motion.y;
                // If the mouse is moving to the left
                /*if (event.motion.xrel < 0)
                    leftPressed = true;
                // If the mouse is moving to the right
                else if (event.motion.xrel > 0)
                    rightPressed = true;
                // If the mouse is moving up
                else if (event.motion.yrel < 0)
                    upPressed = true;
                // If the mouse is moving down
                else if (event.motion.yrel > 0)
                    downPressed = true;*/
                break;
            case SDL_QUIT:
                gs = GS_DONE;
                break;
            case SDL_KEYDOWN:
                KEYS[event.key.keysym.sym] = true;
                break;
            case SDL_KEYUP:
                KEYS[event.key.keysym.sym] = false;
                break;
            default:
                break;
			}
        }
}

void Game::backGround() {
    // draw background
    for(int y = -gsr->get(level->backgroundImage)->getWidth(); y <= screen->h; y += gsr->get(level->backgroundImage)->getHeight()) {
        for(int x = 0; x <= screen->w; x += gsr->get(level->backgroundImage)->getWidth()) {
            gsr->get(level->backgroundImage)->draw(screen, x, y+level->levelY);
        }
    }
    level->levelY += level->levelScrollSpeed;
    if(level->levelY > gsr->get(level->backgroundImage)->getHeight()) {
        level->levelY = 0;
    }
}

void Game::handleEnemies() {
    for(int i = 0; i < MAX_ENEMIES; i++) {
        if(enemies[i].exists) {
            enemies[i].x += enemies[i].speedX;
            enemies[i].y += enemies[i].speedY;
            enemies[i].draw(screen, enemies[i].x, enemies[i].y);
            if(enemies[i].y < -100 || enemies[i].y > screen->h + 100 ||
                enemies[i].x < -100 || enemies[i].x > screen->w + 100) {
                enemies[i].exists = false;
            }
            if(enemies[i].armor < 0) {
                enemies[i].exists = false;

                addExplosion(SR_EXPLOSION_1, enemies[i].x,  enemies[i].y);
            }

            if(enemies[i].image->rectCollide(enemies[i].x, enemies[i].y, *player->image, player->x, player->y)) {
                if(enemies[i].image->pixelCollide(enemies[i].x, enemies[i].y, *player->image, player->x, player->y)) {
                    enemies[i].armor -= player->bullets[i].damage;
                    player->bullets[i].exists = false;
                    addExplosion(SR_EXPLOSION_1, enemies[i].x,  enemies[i].y);
                }
            }
        }
    }
}

void Game::handleBullets() {
    for(int i = 0; i < MAX_BULLETS; i++) {
        if(player->bullets[i].exists) {

            bf->process(player->bullets[i]);

            //collision
            for(int j = 0; j < MAX_ENEMIES; j++) {
                if(enemies[j].exists == true ) {
                    if(enemies[j].image->rectCollide(enemies[j].x, enemies[j].y, *player->bullets[i].image, player->bullets[i].x, player->bullets[i].y)) {
                        if(enemies[j].image->pixelCollide(enemies[j].x, enemies[j].y, *player->bullets[i].image, player->bullets[i].x, player->bullets[i].y)) {
                            enemies[j].armor -= player->bullets[i].damage;
                            player->bullets[i].exists = false;
                        }
                    }
                }
            }

            //mouse collision
            if(player->bullets[i].y > player->bullets[i].targetY -10 && player->bullets[i].y < player->bullets[i].targetY +10){
                player->bullets[i].exists = false;
                addExplosion(SR_EXPLOSION_1, player->bullets[i].x,  player->bullets[i].y);
            }

            player->bullets[i].draw(screen, player->bullets[i].x, player->bullets[i].y);


            //destroy if oolos
            if(player->bullets[i].y < -50 || player->bullets[i].y > screen->h +50 ||
                    player->bullets[i].x < -50 || player->bullets[i].x > screen->w +50) {
                player->bullets[i].exists = false;
            }
        }
    }
}

void Game::shootbeam(int beam) {

    if(beam == PLAYER_BEAM_NORMAL) {
        player->lastShot = SDL_GetTicks();

        int center = player->x + player->image->getWidth()/2 - gsr->get(SR_BEAM_1)->getWidth()/2;
        player->addBullet(gsr->get(SR_BEAM_1), center , player->y - 10, 8, 1, mouseX, mouseY, 1, BULLET_FLIGHT_NORMAL);
        //player->addBullet(gsr->get(SR_BEAM_1), center + 13, player->y - 10, 8, -sqrt(336), mouseX, mouseY, 1, BULLET_FLIGHT_NORMAL);
        //player->addBullet(gsr->get(SR_BEAM_1), center - 13, player->y - 10, -8, -sqrt(336), mouseX, mouseY, 1, BULLET_FLIGHT_NORMAL);
        //player->addBullet(gsr->get(SR_BEAM_1), center + 13, player->y - 10, 12, -sqrt(266), mouseX, mouseY, 1, BULLET_FLIGHT_NORMAL);
        /*player->addBullet(gsr->get(SR_BEAM_1), center - 13, player->y - 10, -12, -sqrt(266), 1, BULLET_FLIGHT_NORMAL);
        player->addBullet(gsr->get(SR_BEAM_1), center + 13, player->y - 10, 16, -sqrt(204), 1, BULLET_FLIGHT_NORMAL);
        player->addBullet(gsr->get(SR_BEAM_1), center - 13, player->y - 10, -16, -sqrt(204), 1, BULLET_FLIGHT_NORMAL);
        player->addBullet(gsr->get(SR_BEAM_1), center + 13, player->y - 10, 18, -sqrt(76), 1, BULLET_FLIGHT_NORMAL);
        player->addBullet(gsr->get(SR_BEAM_1), center - 13, player->y - 10, -18, -sqrt(76), 1, BULLET_FLIGHT_NORMAL);
        player->addBullet(gsr->get(SR_BEAM_1), center + 13, player->y - 3, 20, 0, 1, BULLET_FLIGHT_NORMAL);
        player->addBullet(gsr->get(SR_BEAM_1), center - 13, player->y - 3, -20, 0, 1, BULLET_FLIGHT_NORMAL);

        player->addBullet(gsr->get(SR_BEAM_1), center + 13, player->y + 5, 0, 20, 1, BULLET_FLIGHT_NORMAL);
        player->addBullet(gsr->get(SR_BEAM_1), center - 13, player->y + 5, 0, 20, 1, BULLET_FLIGHT_NORMAL);
        player->addBullet(gsr->get(SR_BEAM_1), center + 13, player->y + 5, 4, sqrt(384), 1, BULLET_FLIGHT_NORMAL);
        player->addBullet(gsr->get(SR_BEAM_1), center - 13, player->y + 5, -4, sqrt(384), 1, BULLET_FLIGHT_NORMAL);
        player->addBullet(gsr->get(SR_BEAM_1), center + 13, player->y + 5, 8, sqrt(336), 1, BULLET_FLIGHT_NORMAL);
        player->addBullet(gsr->get(SR_BEAM_1), center - 13, player->y + 5, -8, sqrt(336), 1, BULLET_FLIGHT_NORMAL);
        player->addBullet(gsr->get(SR_BEAM_1), center + 13, player->y + 5, 12, sqrt(266), 1, BULLET_FLIGHT_NORMAL);
        player->addBullet(gsr->get(SR_BEAM_1), center - 13, player->y + 5, -12, sqrt(266), 1, BULLET_FLIGHT_NORMAL);
        player->addBullet(gsr->get(SR_BEAM_1), center + 13, player->y + 5, 16, sqrt(204), 1, BULLET_FLIGHT_NORMAL);
        player->addBullet(gsr->get(SR_BEAM_1), center - 13, player->y + 5, -16, sqrt(204), 1, BULLET_FLIGHT_NORMAL);
        player->addBullet(gsr->get(SR_BEAM_1), center + 13, player->y + 5, 18, sqrt(76), 1, BULLET_FLIGHT_NORMAL);
        player->addBullet(gsr->get(SR_BEAM_1), center - 13, player->y + 5, -18, sqrt(76), 1, BULLET_FLIGHT_NORMAL);*/

    } else if(beam == PLAYER_BEAM_CHARGE) {

    }

}

void Game::handleLevel() {
    while(level->isNextEvent()) {
        Command* c = level->lvl_cmds.at(0);
        //if(c->cmd ==
        cout << "Next Event" << endl;
        if(c->cmd == 'E') {

            int i = getEmptyEnemy();
            if(i != -1) {
                cout << "Next Event - Add Enemy" << endl;
                enemies[i].exists = true;
                enemies[i].image = gsr->get(c->p1);
                enemies[i].x = c->p2;
                enemies[i].y = c->p3;
                enemies[i].shotDelay = c->p4;
                enemies[i].damage = c->p5;
                enemies[i].armor = c->p6;
                enemies[i].beam = c->p7;
                enemies[i].flightType = c->p8;
                enemies[i].speedX = c->p9;
                enemies[i].speedY = c->p10;
            }
        }


        level->lvl_cmds.erase(level->lvl_cmds.begin() + 0);
    }

}

void Game::handleExplosions() {
    for(int i = 0; i < MAX_EXPLOSIONS; i++) {
        if(explosions[i].exists) {
            if(SDL_GetTicks() - explosions[i].startTime >=  explosions[i].duration) {
                explosions[i].exists = false;
            } else {
                explosions[i].draw(screen, explosions[i].x, explosions[i].y);
            }
        }
    }
}

int Game::getEmptyEnemy() {
    for(int i = 0; i < MAX_ENEMIES; i++) {
        if(!enemies[i].exists) {
            return i;
        }
    }
    return -1;
}

int Game::getEmptyExplosion() {
    for(int i = 0; i < MAX_EXPLOSIONS; i++) {
        if(!explosions[i].exists) {
            return i;
        }
    }
    return -1;
}

void Game::addExplosion(int image, int x, int y) {
    int i = getEmptyExplosion();
    if(i > -1) {
        explosions[i].exists = true;
        explosions[i].image = gsr->get(image);
        explosions[i].startTime = SDL_GetTicks();
        explosions[i].duration = explosions[i].image->speed * explosions[i].image-> maxFrames;
        explosions[i].x = x;
        explosions[i].y = y;
    }
}
