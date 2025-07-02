#include "GameState.h"
#include "MenuState.h"
#include "ResourceManager.h"
#include "LevelState.h"
void GameState::nextLevel()
{
    currentLevelID++;
    if (currentLevelID> 3) {  
        currentLevelID = 0;
    }
    playerMemento = currentLevel->getPlayerData(); // Reset player data for the new level

    currentLevel = std::make_unique<Level>(currentLevelID,this,*this->playerMemento.get()); // Create a new level with the updated player data
}
GameState::GameState(StateManager *manager) :currentLevelID(0), State(manager),
                                              menuButton(Vector2{50, 50}, Vector2{50, 50}),playerMemento(std::make_unique<PlayerData>(3, 0, 0))
{
    currentLevel = std::make_unique<Level>(currentLevelID,this,*this->playerMemento.get()); // Initialize the first level
    menuButton.setPrimaryTexture(ResourceManager::getInstance().getTexture("GAME_STATE_MENU_BUTTON"))
        .DisableBackground()
        .fitTexture();  
}


void GameState::resetLevelWhenMarioDead()
{
    playerMemento = currentLevel->getPlayerData(); // Get the player data from the current level
    currentLevel = std::make_unique<Level>(currentLevelID, this, *playerMemento.get()); // Reset the level with the current player data
}



void GameState::drawLevelEndSummary()
{
    DrawRectangleRounded(Rectangle{(float)GetScreenWidth() / 2 - 400, (float)GetScreenHeight() / 2 - 350, 800, 700}, 0.2f, 180, Color{255, 215, 137, 220}); // Semi-transparent background
      DrawRectangleRoundedLinesEx(Rectangle{(float)GetScreenWidth() / 2 - 400, (float)GetScreenHeight() / 2 - 350, 800, 700}, 0.2f, 180, 10.0f, Color{234,136,65,255}); // Border around the rectangle
    // Display summary or transition effects
    DrawTextureNPatch(ResourceManager::getInstance().getTexture("LEVEL_END_CONGRATULATIONS"),
                       NPatchInfo{Rectangle{0, 0, (float)ResourceManager::getInstance().getTexture("LEVEL_END_CONGRATULATIONS").width,
                                           (float)ResourceManager::getInstance().getTexture("LEVEL_END_CONGRATULATIONS").height}, 0, 0, 0, 0},
                       Rectangle{(float)GetScreenWidth() / 2 - 400, (float)GetScreenHeight() / 2 - 300, 800, 120}, Vector2{0, 0}, 0.0f, WHITE);
      std::string summarry = "Level " + std::to_string(currentLevelID) + " Complete!";
      DrawTextEx(ResourceManager::getInstance().getFonts("HUD_FONT"), summarry.c_str(),
                       Vector2{(float)GetScreenWidth() / 2 - MeasureText(summarry.c_str(), 60) / 2, (float)GetScreenHeight() / 2 - 150}, 60, 2, GOLD);
      DrawText(("Scores: " + std::to_string(0)).c_str(), GetScreenWidth() / 2 - MeasureText(("Scores: " + std::to_string(0)).c_str(), 100) / 2, GetScreenHeight() / 2 + 10, 100, WHITE);
      DrawTextureNPatch(ResourceManager::getInstance().getTexture("LEVEL_END_ENTER"),
                       NPatchInfo{Rectangle{0, 0, (float)ResourceManager::getInstance().getTexture("LEVEL_END_ENTER").width,
                                           (float)ResourceManager::getInstance().getTexture("LEVEL_END_ENTER").height}, 0, 0, 0, 0},
                       Rectangle{(float)GetScreenWidth() / 2 -700, (float)GetScreenHeight() / 2+100 , 1400, 400}, Vector2{0, 0}, 0.0f, WHITE);
}

void GameState::update()
{
        menuButton.update();
    if (menuButton.isClicked()) {
        stateManager->setState(new MenuState(stateManager));  // Switch to MenuState
    }
    switch (currentLevel->getState()) {
    
    case LevelState::LEVEL_STATE_PLAYING:
        currentLevel->UpdateLevel();  // Update the current level
        break;
    case LevelState::LEVEL_STATE_COMPLETED:
        drawLevelEndSummary();  // Draw level end summary
        if (IsKeyPressed(KEY_ENTER)) {
            nextLevel();  // Proceed to the next level when Enter is pressed
        }
        break;
    case LevelState::LEVEL_STATE_NEED_RESET:
    if(IsKeyPressed(KEY_ENTER)) {
            resetLevelWhenMarioDead();  // Reset the level when Enter is pressed
        }
        break;
    default:
        break;
    }

}
void GameState::draw(){

    currentLevel->DrawLevel();
    gameHUD.Draw();
    menuButton.Draw();
    if (currentLevel->IsCompleted()) {
        drawLevelEndSummary();  // Draw level end summary
    }
    
   
}