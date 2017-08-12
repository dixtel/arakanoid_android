#include "include/statemachine.h"

StateMachine::~StateMachine() {

    currentState = nullptr;
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

void StateMachine::DeleteStates() {

     SDL_Log("%i", states.size());

    for (std::map <stateType, State*>::iterator it = states.begin(); it != states.end(); ++it) {
        SDL_Log("%i", (*it).first);

        delete it->second;
        it->second = nullptr;
        states.erase(it);

        DeleteStates();
        break;
    }
}

bool StateMachine::IsGameExit() {

    return currentState->IsGameExit();
}
