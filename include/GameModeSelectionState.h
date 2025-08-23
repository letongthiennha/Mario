#pragma once
#pragma once
#include "State.h"
#include "Button.h"
#include "Button2.h"

class GameModeSelectionState : public State {
public:
    GameModeSelectionState(StateManager* manager);
    ~GameModeSelectionState();

    void update() override;
    void draw() override;

private:
    Button newGameButton;
    Button continueButton;
    Button leaderboardButton;
    Button2 backButton;
	Texture2D titleTexture;

    Texture2D mushroomTexture;
	Texture2D marioTexture;
	Texture2D luigiTexture;
};