#include "Level.h"

Level::Level() {

}

Level::~Level() {

}

/*void Level::loadLevel(string file) {
    char str[80];
    float f;
    char c = '-';
    FILE* pFile;
    pFile = fopen(file.c_str(),"r");
    while(c != 'F') {
        fscanf(pFile, "%c", &c);
        Command s;
        s.cmd = c;
        switch(c) {
            case 'S':
                cout << "Start of Level" << endl;
                break;
            case 'F':
                cout << "Finished Loading Level" << endl;
                break;
            case 'E':
                cout << "Enemy Loaded" << endl;
                fscanf(pFile, " %f %f %f", &s.p1, &s.p2, &s.p3);
                break;
            case 'B':
                cout << "Boss Loaded" << endl;
                break;
            default:
                break;
        }
    }

    fclose(pFile);
}*/
void Level::loadLevel(int level) {
    lvl_cmds = vector<Command*>();
    if(level == 1) {
        addEnemyToQueue(2800, SR_ENEMY_1, 600, 100, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, -1, 0);
        addEnemyToQueue(2900, SR_ENEMY_1, 40, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 1);
        addEnemyToQueue(3000, SR_ENEMY_1, 80, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 2);
        addEnemyToQueue(3100, SR_ENEMY_1, 120, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 3);
        /*addEnemyToQueue(3200, SR_ENEMY_1, 160, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(3300, SR_ENEMY_1, 200, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(3400, SR_ENEMY_1, 240, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(3500, SR_ENEMY_1, 280, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(3600, SR_ENEMY_1, 320, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(3700, SR_ENEMY_1, 360, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(3800, SR_ENEMY_1, 400, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(3900, SR_ENEMY_1, 440, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(4000, SR_ENEMY_1, 480, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(4100, SR_ENEMY_1, 520, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(4200, SR_ENEMY_1, 560, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(4300, SR_ENEMY_1, 600, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);


        addEnemyToQueue(8800, SR_ENEMY_1, 600, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(8900, SR_ENEMY_1, 560, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(9000, SR_ENEMY_1, 520, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(9100, SR_ENEMY_1, 480, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(9200, SR_ENEMY_1, 440, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(9300, SR_ENEMY_1, 400, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(9400, SR_ENEMY_1, 360, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(9500, SR_ENEMY_1, 320, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(9600, SR_ENEMY_1, 280, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(9700, SR_ENEMY_1, 240, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(9800, SR_ENEMY_1, 200, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(9900, SR_ENEMY_1, 160, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(10000, SR_ENEMY_1, 120, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(10100, SR_ENEMY_1, 80, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(10200, SR_ENEMY_1, 40, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);
        addEnemyToQueue(10300, SR_ENEMY_1, 0, 0, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, 8);*/


        addEnemyToQueue(12500, SR_ENEMY_1, 320, 480, 90, 1, 1, PLAYER_BEAM_NORMAL, FLIGHT_NORMAL, 0, -8);

    }
}


void Level::addEnemyToQueue(int timer, int image, int posX, int posY, int shotDelay, int damage, int armor, int beam, int flightType, int speedX, int speedY) {
    Command* c = new Command();

    c->cmd = 'E';
    c->timer = timer;
    c->p1 = SR_ENEMY_1;
    c->p2 = posX;
    c->p3 = posY;
    c->p4 = shotDelay;
    c->p5 = damage;
    c->p6 = armor;
    c->p7 = beam;
    c->p8 = flightType;
    c->p9 = speedX;
    c->p10 = speedY;

    lvl_cmds.push_back(c);
}

bool Level::isNextEvent() {
    if(lvl_cmds.size() > 0) {
         // cout << "SDL_GETTICKS(): " << SDL_GetTicks() << " levelstarttime: " << levelStartTime << " event timer: " << lvl_cmds.at(0)->timer << " event cmd: " << lvl_cmds.at(0)->cmd << " event p1: " << lvl_cmds.at(0)->p1<< endl;
     //   vector<Command*>::iterator ii = lvl_cmds.begin();
        if(SDL_GetTicks() - levelStartTime >= lvl_cmds.at(0)->timer ) {
            return true;
        }
    }
    return false;
}

Command* Level::nextEvent() {
    vector<Command*>::iterator ii = lvl_cmds.begin();
    return (*ii);
}


