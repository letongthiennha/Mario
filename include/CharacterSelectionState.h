#pragma once
#include "StateManager.h"
#include "CharacterSelectionState.h"
#include "CharacterFactory.h"
#include "PlayableCharacter.h"
#include "Button.h"
class CharacterSelectionState : public State {
private:
    Button marioButton;
    Button luigiButton;
    Button home;


public:
    CharacterSelectionState(StateManager *manager);
    ~CharacterSelectionState();
    void update() override;
    void draw() override;
};