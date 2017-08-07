#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include <SDL.h>

#include "include/statemachine.h"
#include "include/buttonmanager.h"
#include "include/vector2.h"
#include "include/render.h"
#include "include/text.h"
#include "include/rectangle.h"

#include <memory>


class PauseState : public State {

    Render                *render = nullptr;
    StateMachine          *stateMachine;
    ButtonManager          buttonManager;
    std::unique_ptr <Text> pauseText;
    Rectangle              baseBackgroundImage;

    unsigned width;
    unsigned height;

    bool mouseLeftClick;
    Vector2 <int> mousePosition;

    void HandleEvent();
public:

    PauseState(unsigned width, unsigned height, StateMachine *stateMachne, SDL_Renderer *ren);
    ~PauseState();

    void Update(float elapsedTime);
    void RenderScene();
    void OnEnter();
    void OnExit();
};

#endif // PAUSESTATE_H
