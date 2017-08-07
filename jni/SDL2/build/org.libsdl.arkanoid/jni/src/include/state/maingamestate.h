#ifndef MAINGAMESTATE_H
#define MAINGAMESTATE_H

#include <SDL2/SDL.h>

#include "include/statemachine.h"
#include "include/buttonmanager.h"
#include "include/rectangle.h"
#include "include/render.h"
#include "include/player.h"
#include "include/ball.h"
#include "include/logsdlerror.h"
#include "include/collision.h"
#include "include/mapbrick.h"
#include "include/brickmanager.h"
#include "include/text.h"
#include "include/scoresysytem.h"

#include <iostream>
#include <string>
#include <memory>


class MainGameState : public State {

    Render        *render = nullptr;
    StateMachine  *stateMachine = nullptr;
    ButtonManager  buttonManager;
    Player         player;
    Ball           ball;
    Border         border;
    Collision      collision;
    MapBrick       mapBrick;
    BrickManager   brickManager;
    ScoreSystem    scoreSystem;
    Rectangle      backgroungImage;
    Rectangle      baseBackgroungImage;
    Rectangle      scoreboardImage;
    Rectangle      pipeImage;
    std::unique_ptr <Text> levelNumberText;
    std::unique_ptr <Text> currentPointsText;
    std::unique_ptr <Text> bestPointsText;


    std::vector <std::string> pathsToMaps;
    unsigned currentMapNumber;
    unsigned numbersOfMaps;

    unsigned       width;
    unsigned       height;
    bool           mouseLeftClick;
    bool           exitGame;
    bool           winGame;
    Vector2 <int>  mousePosition;

    void HandleEvent();
public:

    MainGameState(unsigned width, unsigned height, StateMachine *stateMachne, SDL_Renderer *ren);
    ~MainGameState();

    void Update(float elapsedTime);
    void RenderScene();
    void OnEnter();
    void OnExit();
    bool IsGameExit();
};

#endif // MAINGAMESTATE_H
