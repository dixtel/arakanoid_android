#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "include/state.h"

#include <map>
#include <string>
#include <iostream>
#include <utility>

enum stateType {
    mainGameState,
    mainMenuState,
    pauseState,
};

class StateMachine {

    std::map <stateType, State*> states;
    State *currentState = nullptr;

public:

    ~StateMachine();

    void Update(float elapsedTime);
    void RenderScene();
    void Change(const stateType stateName);
    void Add(const stateType stateName, State *state);
    void DeleteStates();
    bool IsGameExit();
};

#endif // STATEMACHINE_H
