#include "GameState.h"
#include "MenuState.h"
#include "ResourceManager.h"
GameState::GameState(StateManager *manager): State(manager),
    menuButton(Vector2{50, 50}, Vector2{50, 50})
{
    menuButton.setPrimaryTexture(ResourceManager::getInstance().getTexture("GAME_STATE_MENU_BUTTON"))
        .DisableBackground()
        .fitTexture();
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