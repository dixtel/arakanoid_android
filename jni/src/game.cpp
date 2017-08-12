#include "include/game.h"

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

Game::Game(const unsigned SCREEN_WIDTH, const unsigned SCREEN_HEIGHT, const std::string SCREEN_TITLE) {

    this->SCREEN_WIDTH = SCREEN_WIDTH;
    this->SCREEN_HEIGHT = SCREEN_HEIGHT;
    this->SCREEN_TITLE = SCREEN_TITLE;
}

Game::~Game() {

}

bool Game::InitGame() {

    win = SDL_CreateWindow(SCREEN_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

    if (win == nullptr || ren == nullptr) {

        PrintError("SDL_CreateWindow, SDL_CreateRenderer");
        return false;
    }

    SDL_DisplayMode display;

    if (SDL_GetCurrentDisplayMode(0, &display) != 0) {

        PrintError("SDL_GetCurrentDisplayMode");
        return false;
    }

    float scalex = 1 + (float(display.w - SCREEN_WIDTH) / SCREEN_WIDTH);
    float scaley = 1 + (float(display.h - SCREEN_HEIGHT) / SCREEN_HEIGHT);

    PrintError(to_string(scalex) + " " + to_string(scaley));

    if (SDL_RenderSetScale(ren, scalex, scaley) != 0) {

        PrintError("SDL_RenderSetLogicalSize");
        return false;
    }

    SDL_Log("%s %s", "PATH PRF:", SDL_GetPrefPath("My Company", "Arkanoid"));

    stateMachine = new StateMachine();

    return true;
}

bool Game::InitSDL() {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {

        PrintError("SDL_Init");
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)) {

        PrintError("IMG_Init");
        SDL_Quit();
        return false;
    }

    if (TTF_Init() != 0) {

        PrintError("TTF_Init");
        SDL_Quit();
        IMG_Quit();
        return false;
    }

    return true;
}

bool Game::InitStates() {

    stateMachine->Add(stateType::pauseState,    new PauseState(SCREEN_WIDTH, SCREEN_HEIGHT, stateMachine, ren));
    stateMachine->Add(stateType::mainMenuState, new MainMenuState(SCREEN_WIDTH, SCREEN_HEIGHT, stateMachine, ren));
    stateMachine->Add(stateType::mainGameState, new MainGameState(SCREEN_WIDTH, SCREEN_HEIGHT, stateMachine, ren));

    stateMachine->Change(stateType::mainMenuState);

    return true;
}

void Game::Start() {

    Time time;

    float elapsedTime = 0;

    while (true) {

        elapsedTime = time.GetTicks() / 1000;
        time.StartTicks();

        stateMachine->Update(elapsedTime);
        stateMachine->RenderScene();

        if (stateMachine->IsGameExit()) {

            break;
        }
    }

    Quit();
}

void Game::Quit() {

    delete stateMachine;
    stateMachine = nullptr;

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}
