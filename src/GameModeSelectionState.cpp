#include "GameModeSelectionState.h"
#include "StateManager.h"
#include "CharacterSelectionState.h"
#include "MenuState.h"
#include "ResourceManager.h"

GameModeSelectionState::GameModeSelectionState(StateManager* manager) : State(manager),
newGameButton(Vector2{ (float)GetScreenWidth() / 4 - 150, (float)GetScreenHeight() / 2 - 75 }, Vector2{ 300, 50 }),
continueButton(Vector2{ (float)GetScreenWidth() / 4 - 150, (float)GetScreenHeight() / 2 + 25 }, Vector2{ 300, 50 }),
designGameButton(Vector2{ (float)GetScreenWidth() * 3 / 4 - 150, (float)GetScreenHeight() / 2 - 75 }, Vector2{ 300, 50 }),
leaderboardButton(Vector2{ (float)GetScreenWidth() * 3 / 4 - 150, (float)GetScreenHeight() / 2 + 25 }, Vector2{ 300, 50 }),
twoPlayerButton(Vector2{ (float)GetScreenWidth() / 2 - 150, (float)GetScreenHeight() / 2 + 150 }, Vector2{ 300, 50 }),
backButton(Vector2{ 50, 50 }, Vector2{ 50, 50 })
{
    titleTexture = ResourceManager::getInstance().getTexture("SELECT_GAME_MODE_TITLE");

    newGameButton.setText("New Game");
    continueButton.setText("Continue");
    designGameButton.setText("Design Game");
    leaderboardButton.setText("Leaderboard");
    twoPlayerButton.setText("2 Player");

    backButton.setPrimaryTexture(ResourceManager::getInstance().getTexture("MENU_BUTTON_RELEASE")).DisableBackground().fitTexture();
}

GameModeSelectionState::~GameModeSelectionState() {
}

void GameModeSelectionState::update() {
    newGameButton.update();
    continueButton.update();
    designGameButton.update();
    leaderboardButton.update();
    twoPlayerButton.update();
    backButton.update();

    if (newGameButton.isClicked()) {
        stateManager->setState(new CharacterSelectionState(stateManager));
    }
    else if (continueButton.isClicked()) {
        // Placeholder: Add logic to continue a game
    }
    else if (designGameButton.isClicked()) {
        // Placeholder: Add logic for a map editor or design state
    }
    else if (leaderboardButton.isClicked()) {
        // Placeholder: Add logic for a leaderboard state
    }
    else if (twoPlayerButton.isClicked()) {
        // Placeholder: Add logic for 2 player mode
    }
    else if (backButton.isClicked()) {
        stateManager->setState(new MenuState(stateManager));
    }
}

void GameModeSelectionState::draw() {
    ClearBackground(Color{ 255, 210, 29, 255 });
    DrawTexture(titleTexture, GetScreenWidth() / 2 - titleTexture.width / 2, 0, WHITE);

    newGameButton.Draw();
    continueButton.Draw();
    designGameButton.Draw();
    leaderboardButton.Draw();
    twoPlayerButton.Draw();
    backButton.Draw();
}