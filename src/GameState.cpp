#include "GameState.h"
#include "MenuState.h"
#include "ResourceManager.h"
void GameState::nextLevel()
{
    currentLevelID++;
    if (currentLevelID> 3) {  
        currentLevelID = 0;
    }
    currentLevel = std::make_unique<Level>(currentLevelID,this);  
}
GameState::GameState(StateManager *manager) :currentLevelID(0), State(manager),
                                              menuButton(Vector2{50, 50}, Vector2{50, 50})
{
    currentLevel = std::make_unique<Level>(currentLevelID,this); 
    menuButton.setPrimaryTexture(ResourceManager::getInstance().getTexture("GAME_STATE_MENU_BUTTON"))
        .DisableBackground()
        .fitTexture();  
}

void GameState::onLevelEnd()
{
    // Display summary or transition effects
    DrawText(summarry.c_str(), GetScreenWidth() / 2 - MeasureText(summarry.c_str(), 20) / 2, GetScreenHeight() / 2 - 10, 20, WHITE);
    if(IsKeyPressed(KEY_ENTER))  // Wait for user input to continue 
    nextLevel();  // Load the next level
}

void GameState::update()
{
    if (!currentLevel->IsCompleted()) {
        currentLevel->UpdateLevel();
    } else {
        onLevelEnd();  // Handle level completion
    }
    menuButton.update();
    if (menuButton.isClicked()) {
        stateManager->setState(new MenuState(stateManager));  // Switch to MenuState
    }
}
void GameState::draw(){

    currentLevel->DrawLevel();
    gameHUD.Draw();
    menuButton.Draw();
}