#pragma once
#include "State.h"
class State;
class StateManager {
    private:
        State *currentState;
    public:
        StateManager();
        ~StateManager();

        void setState(State *newState);

        void update();

        void draw();
};