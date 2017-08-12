#include "include/game.h"
#include "include/logerror.h"

#include <SDL.h>

#include <string>
#include <sstream>

const unsigned WINDOW_WIDTH = 640;
const unsigned WINDOW_HEIGHT = 960;
const std::string WINDOW_TITLE = "Arkanoid";


int main(int argv, char ** args) {
    Game game(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    if (!game.InitSDL()) {

        PrintError("InitSDL");
        return 1;
    }

    if (!game.InitGame()) {

        PrintError("InitGame");
        return 1;
    }

    if (!game.InitStates()) {

        PrintError("InitStates");
        return 1;
    }

    game.Start();

    return 0;
}