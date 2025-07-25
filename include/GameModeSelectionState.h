#pragma once
#pragma once
#include "State.h"
#include "Button.h"

class GameModeSelectionState : public State {
public:
    GameModeSelectionState(StateManager* manager);
    ~GameModeSelectionState();

    void update() override;
    void draw() override;

private:
    Button newGameButton;
    Button continueButton;
    Button designGameButton;
    Button leaderboardButton;
    Button backButton;
    Button twoPlayerButton;
	Texture2D titleTexture;
};