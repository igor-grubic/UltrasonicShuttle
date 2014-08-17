#include "main.h"

const int FRAMES_PER_SECOND = 60;

int main ( int argc, char** argv ) {
    Game game = Game();
    if(game.init() > 0 ) {
        cout << "Error occured in Game initialization!" << endl;
        return 1;
    }
    game.gs = GS_MAIN;

    int startTicks = SDL_GetTicks();
    int currentTicks = 0;

    while (game.gs != GS_DONE) {
        if(game.gs == GS_MAIN) {
            game.run();

            currentTicks = SDL_GetTicks() - startTicks;
            if(currentTicks < 1000 / FRAMES_PER_SECOND )
            {
                SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - currentTicks );
                startTicks = SDL_GetTicks();
            }
        }
    }

    printf("Exited cleanly\n");
    return 0;
}
