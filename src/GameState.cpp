#include "GameState.h"
#include "MenuState.h"
#include "ResourceManager.h"
GameState::GameState(StateManager *manager): State(manager),
    menuButton(Vector2{50, 50}, Vector2{50, 50}, "", &ResourceManager::getInstance().getTexture("GAME_STATE_MENU_BUTTON"), WHITE, LIGHTGRAY, DARKGRAY)
{
    menuButton.setTextSize(10);
    menuButton.OffBackground();
    menuButton.fitTexture();
    // gameWorld.InitWorld();
}

void GameState::update(){
    gameWorld.UpdateWorld();
    menuButton.update();
    if (menuButton.isClicked()) {
        stateManager->setState(new MenuState(stateManager));  // Switch to MenuState
    }
}
void GameState::draw(){
    gameWorld.DrawWorld();
    menuButton.Draw();
}