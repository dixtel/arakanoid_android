#include "include/game.h"

Game::Game(const unsigned SCREEN_WIDTH, const unsigned SCREEN_HEIGHT, const std::string SCREEN_TITLE) {

    this->SCREEN_WIDTH = SCREEN_WIDTH;
    this->SCREEN_HEIGHT = SCREEN_HEIGHT;
    this->SCREEN_TITLE = SCREEN_TITLE;
}

Game::~Game() {

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);

    delete stateMachine;
    stateMachine = nullptr;
}

bool Game::InitGame() {

    win = SDL_CreateWindow(SCREEN_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //SDL_RenderSetScale(ren, ;

    stateMachine = new StateMachine();

    if (win == nullptr || ren == nullptr) {
        LogSDLError(std::cout, "SDL_CreateWindow, SDL_CreateRenderer");
        return false;
    }

    return true;
}

bool Game::InitSDL() {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        LogSDLError(std::cout, "SDL_Init");
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)) {
        LogSDLError(std::cout, "IMG_Init");
        return false;
    }

    if (TTF_Init() != 0) {
        LogSDLError(std::cout, "TTF_Init");
        return false;
    }

    return true;
}

bool Game::InitStates() {

    stateMachine->Add(stateType::pauseState, new PauseState(SCREEN_WIDTH, SCREEN_HEIGHT, stateMachine, ren));
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

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}
