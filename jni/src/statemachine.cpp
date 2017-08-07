#include "include/statemachine.h"

StateMachine::~StateMachine() {

    for (std::map <stateType, State*>::iterator it = states.begin(); it != states.end(); ++it) {

        delete it->second;
        states.erase(it);
    }
}

void StateMachine::Update(float elapsedTime) {

    currentState->Update(elapsedTime);
}

void StateMachine::RenderScene() {

    currentState->RenderScene();
}

void StateMachine::Change(const stateType stateName) {

    if (currentState != nullptr) {

        currentState->OnExit();
    }

    bool find = false;

    for (std::map <stateType, State*>::iterator it = states.begin(); it != states.end(); ++it) {

        if (it->first == stateName) {

            currentState = it->second;

            find = true;

            break;
        }
    }

    if (!find) {

        std::cout << stateName << " stateName not found." << std::endl;
    }

    currentState->OnEnter();
}

void StateMachine::Add(const stateType stateName, State *state) {

    states.insert(std::make_pair(stateName, state));
}

bool StateMachine::IsGameExit() {

    return currentState->IsGameExit();
}
