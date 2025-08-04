#pragma once
#include "StateManager.h"
#include "CharacterSelectionState.h"
#include "CharacterFactory.h"
#include "PlayableCharacter.h"
#include "Button.h"
#include "Button2.h"
class CharacterSelectionState : public State {
private:
    Button marioButton;
    Button luigiButton;
    Button2 home;
    Texture2D titleTexture;

public:
    CharacterSelectionState(StateManager *manager);
    ~CharacterSelectionState();
    void update() override;
    void draw() override;
};