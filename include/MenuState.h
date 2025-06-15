#pragma once
#include "State.h"
#include "Button.h"
class MenuState : public State {
    private:
    Button startButton;
    Button optionsButton;
    Button exitButton;
    Button creditsButton;
    Texture2D* backgroundTexture;
public:
    MenuState(StateManager *Manager);
    ~MenuState();

    void update() override;
    void draw() override;
};
