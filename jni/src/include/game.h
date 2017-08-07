#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "include/statemachine.h"
#include "include/logsdlerror.h"
#include "include/state/maingamestate.h"
#include "include/state/mainmenustate.h"
#include "include/state/pausestate.h"
#include "include/time.h"

#include <string>
#include <map>


class Game {

    unsigned      SCREEN_WIDTH;
    unsigned      SCREEN_HEIGHT;
    std::string   SCREEN_TITLE;

    SDL_Window   *win = nullptr;
    SDL_Renderer *ren = nullptr;

    StateMachine *stateMachine = nullptr;
public:

    Game(const unsigned SCREEN_WIDTH, const unsigned SCREEN_HEIGHT, const std::string SCREEN_TITLE);
    ~Game();

    bool InitGame();
    bool InitSDL();
    bool InitStates();

    void Start();
};

#endif // GAME_H
