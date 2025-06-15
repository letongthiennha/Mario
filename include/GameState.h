#pragma once
#include "StateManager.h"
#include "World.h"
#include "Button.h"
class GameState : public State {
private:
    World gameWorld;
    Button menuButton;
public:
    GameState(StateManager *manager);
    ~GameState();

    // void Enter() override;
    // void Exit() override;

    void update() override;
    void draw() override;
};