#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <SDL.h>

#include "include/statemachine.h"
#include "include/render.h"
#include "include/vector2.h"
#include "include/buttonmanager.h"
#include "include/text.h"
#include "include/rectangle.h"

#include <iostream>
#include <memory>


class MainMenuState : public State {

    Render                *render = nullptr;
    StateMachine          *stateMachine = nullptr;
    ButtonManager          buttonManager;
    Rectangle              baseBackgroungImage;

    std::unique_ptr <Text> welcomeText;

    unsigned       width;
    unsigned       height;
    bool           exitGame;
    bool           mouseLeftClick;
    Vector2 <int>  mousePosition;

    void HandleEvent();
public:

    MainMenuState(unsigned width, unsigned height, StateMachine *stateMachne, SDL_Renderer *ren);
    ~MainMenuState();

    void Update(float elapsedTime);
    void RenderScene();
    void OnEnter();
    void OnExit();
    bool IsGameExit();
};

#endif // MAINMENUSTATE_H
