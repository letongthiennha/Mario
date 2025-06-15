#pragma once
#include "StateManager.h"
class StateManager; 
class State{
    protected:
        StateManager *stateManager;
    public:
        State(StateManager *manager);
        virtual void Enter();
        virtual void Exit();
        virtual void update() = 0;
        virtual void draw() = 0;
};