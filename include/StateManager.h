#pragma once
#include "State.h"
class State;
class StateManager {
    private:
        State *currentState;
        State* previousState;
    public:
        StateManager();
        ~StateManager();

        void setState(State *newState);

        void update();

        void draw();

        State* getPreviousState() const;
        void goBack();
};