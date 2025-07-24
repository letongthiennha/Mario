#include "GameState.h"
#include "MenuState.h"
#include "ResourceManager.h"
#include "LevelState.h"
#include "SoundController.h"
#include "StateManager.h"
#include "SettingMenuState.h"
#include "CharacterType.h"
void GameState::nextLevel()
{
    currentLevelID++;
    if (currentLevelID> 3) {  
        currentLevelID = 0;
    }
    playerMemento = currentLevel->getPlayerData(); // Reset player data for the new level

    currentLevel = std::make_unique<Level>(currentLevelID,this,*this->playerMemento.get(), selectedCharacterType); // Create a new level with the updated player data
}
GameState::GameState(StateManager *manager) :currentLevelID(1), State(manager),
                                              menuButton(Vector2{50, 50}, Vector2{50, 50}),
                                              playerMemento(std::make_unique<PlayerData>(3, 0, 0)),
                                                transitionState(TransitionState::TRANSITION_NONE), gameHUD(CharacterType::MARIO)
{
    menuButton.setPrimaryTexture(ResourceManager::getInstance().getTexture("MENU_BUTTON_RELEASE"))
        .DisableBackground()
        .fitTexture();  
    SoundController::getInstance().StopAllSounds(); // Stop all sounds before starting the game
    SoundController::getInstance().PlayMusic("LEVEL_1_MUSIC"); // Start playing the game music
}
GameState::~GameState()
{
    // Cleanup if necessary
}
GameState::GameState(StateManager *manager, CharacterType characterType)
    : GameState(manager)
{
    gameHUD = HUD(characterType);
    selectedCharacterType = characterType;
    currentLevel = std::make_unique<Level>(currentLevelID,this,*this->playerMemento.get(), selectedCharacterType); // Initialize the first level

}

void GameState::resetLevelWhenPlayerDead()
{
    playerMemento = std::make_unique<PlayerData>(playerMemento->getLives() - 1, 0,0); // Decrease lives by 1
    currentLevel =  std::make_unique<Level>(currentLevelID,this,*this->playerMemento.get(), selectedCharacterType);; // Reset the level with the current player data
}



void GameState::drawLevelEndSummary()
{
    static const Texture2D *LevelEndCongratulation = &ResourceManager::getInstance().getTexture("LEVEL_END_CONGRATULATIONS");
    static const Texture2D *LevelEndEnter = &ResourceManager::getInstance().getTexture("LEVEL_END_ENTER");
    DrawRectangleRounded(Rectangle{(float)GetScreenWidth() / 2 - 400, (float)GetScreenHeight() / 2 - 350, 800, 700}, 0.2f, 180, Color{255, 245, 137, 220}); // Semi-transparent background
      DrawRectangleRoundedLinesEx(Rectangle{(float)GetScreenWidth() / 2 - 400, (float)GetScreenHeight() / 2 - 350, 800, 700}, 0.2f, 180, 10.0f, Color{234,136,65,255}); // Border around the rectangle

    // Display summary or transition effects
    DrawTextureNPatch((*LevelEndCongratulation),
                       NPatchInfo{Rectangle{0, 0, (float)(*LevelEndCongratulation).width,
                                           (float)(*LevelEndCongratulation).height}, 0, 0, 0, 0},
                       Rectangle{(float)GetScreenWidth() / 2 - 400, (float)GetScreenHeight() / 2 - 300, 800, 120}, Vector2{0, 0}, 0.0f, WHITE);

    // Display the level completion message
      std::string summarry = "Level " + std::to_string(currentLevelID) + " Complete!";
      DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), summarry.c_str(),
                       Vector2{(float)GetScreenWidth() / 2 - MeasureTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"),(summarry).c_str(),40,2).x / 2, (float)GetScreenHeight() / 2 - 150}, 40, 2, WHITE);

    // Display the player's score
                        std::string score = "Score: " + std::to_string(currentLevel->getPlayerData()->getScore() );
    DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), score.c_str(),
            Vector2{(float)GetScreenWidth() / 2 - MeasureTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"),(score).c_str(),60,2).x / 2, (float)GetScreenHeight() / 2 }, 60, 2, WHITE);
      
      //Display level end enter message
      DrawTextureNPatch(*LevelEndEnter,
                       NPatchInfo{Rectangle{0, 0, (float)(*LevelEndEnter).width,
                                           (float)(*LevelEndEnter).height}, 0, 0, 0, 0},
                       Rectangle{(float)GetScreenWidth() / 2 -700, (float)GetScreenHeight() / 2+100 , 1400, 400}, Vector2{0, 0}, 0.0f, WHITE);
      DrawTextureNPatch(ResourceManager::getInstance().getTexture("HUD_COINS"),
                       NPatchInfo{Rectangle{0, 0, (float)ResourceManager::getInstance().getTexture("HUD_COINS").width,
                                           (float)ResourceManager::getInstance().getTexture("HUD_COINS").height}, 0, 0, 0, 0},
                       Rectangle{(float)GetScreenWidth() / 2 - 200, (float)GetScreenHeight() / 2 + 100, 70, 70}, Vector2{0, 0}, 0.0f, WHITE);
        std::string coins = "X " + std::to_string(currentLevel->getPlayerData()->getCoins());
        DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), coins.c_str(),
                         Vector2{(float)GetScreenWidth() / 2+50 - MeasureTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"),(coins).c_str(),70,2).x / 2, (float)GetScreenHeight() / 2 + 105}, 70, 2, WHITE);
}

void GameState::resetwhenGameOver()
{
    currentLevelID = 1;  // Reset to the first level
    playerMemento = std::make_unique<PlayerData>(3, 0, 0); // Reset player data
    currentLevel =  std::make_unique<Level>(currentLevelID,this,*this->playerMemento.get(), selectedCharacterType);; // Create a new level with the reset player data
}

void GameState::startTransition(TransitionState state)
{
    transitionState = state;  // Set the transition state
    transitionTimeAcum = 0.0f;  // Reset the transition time accumulator
    switch (state) {
        case TransitionState::TRANSITION_NEXT_LEVEL:
            transitionTime = 5.0f;  // Set transition time for next level
            SoundController::getInstance().StopAllSounds();  // Stop all sounds when transitioning
            break;
        case
        TransitionState::TRANSITION_LEVEL_RESET:
            transitionTime = 5.0f;  // Set transition time for level reset
            SoundController::getInstance().StopAllSounds();  // Stop all sounds when transitioning
            break;
        case TransitionState::TRANSITION_GAME_OVER:
            transitionTime = 5.0f;  // Set transition time for game over
            SoundController::getInstance().StopAllSounds();  // Stop all sounds when transitioning
            break;
        case TransitionState::TRANSITION_NONE:
            transitionTime = 0.0f;  // No transition time when not transitioning
            SoundController::getInstance().StopAllSounds();  // Stop all sounds when not transitioning
            SoundController::getInstance().PlayMusic("LEVEL_"+std::to_string(currentLevelID)+"_MUSIC");  // Restart the game music
            break;
    }
}

void GameState::update()
{
        menuButton.update();
    if (menuButton.isClicked()) {
        stateManager->setState(new SettingMenuState(stateManager));  // Switch to MenuState
    }
    switch (transitionState) {
    case TransitionState::TRANSITION_NEXT_LEVEL:
        transitionTimeAcum += GameClock::getInstance().DeltaTime;  // Accumulate transition time
        if (transitionTimeAcum >= transitionTime) {
            startTransition(TransitionState::TRANSITION_NONE);  // Reset transition state
        }
        break;
    case TransitionState::TRANSITION_LEVEL_RESET:
        transitionTimeAcum += GameClock::getInstance().DeltaTime;  // Accumulate
        if (transitionTimeAcum >= transitionTime) {
            startTransition(TransitionState::TRANSITION_NONE);  // Reset transition state
        }
        break;
    case TransitionState::TRANSITION_GAME_OVER:
        transitionTimeAcum += GameClock::getInstance().DeltaTime;  // Accumulate
        if (transitionTimeAcum >= transitionTime) {
            startTransition(TransitionState::TRANSITION_NONE);  // Reset transition state
        }
    }
    if(transitionState != TransitionState::TRANSITION_NONE) {
        return;  // Skip updates if a transition is in progress
    }
    switch (currentLevel->getState()) {
    
    case LevelState::LEVEL_STATE_PLAYING:
        currentLevel->UpdateLevel();  // Update the current level
        break;
    case LevelState::LEVEL_STATE_COMPLETED:
        if (IsKeyPressed(KEY_ENTER)) {
            nextLevel();  // Load the next level
            startTransition(TransitionState::TRANSITION_NEXT_LEVEL);  // Proceed to the next level when Enter is pressed
        }

        break;
    case LevelState::LEVEL_STATE_NEED_RESET:
    if(IsKeyPressed(GetKeyPressed())) {
        resetLevelWhenPlayerDead();  // Reset the level
            startTransition(TransitionState::TRANSITION_LEVEL_RESET);  // Reset the level when Enter is pressed
        }
        break;
    case LevelState::LEVEL_STATE_GAME_OVER:
        
        if(IsKeyPressed(KEY_ENTER)) {
            resetwhenGameOver();  // Reset the game when Enter is pressed

            startTransition(TransitionState::TRANSITION_GAME_OVER);  // Start game over transition when Enter is pressed            resetwhenGameOver();  // Reset the game when Enter is pressed
        }
        break;
    default:
        break;
    }

}

void GameState::draw(){

    currentLevel->DrawLevel();
    if (currentLevel->IsCompleted()) {
        if(transitionState== TransitionState::TRANSITION_NONE) {
            drawLevelEndSummary();  // Draw level end summary
        }
    }
    
    gameHUD.Draw();


    static const Texture2D *GameOver= &ResourceManager::getInstance().getTexture("GAME_OVER");
    static const Font* SuperMarioFont = &ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT");
    static const Texture2D *SmallMario = &ResourceManager::getInstance().getTexture("SMALL_MARIO_0_RIGHT");
    static const Texture2D *SmallLuigi = &ResourceManager::getInstance().getTexture("SMALL_LUIGI_0_RIGHT");
    if(currentLevel->getState() == LevelState::LEVEL_STATE_GAME_OVER&& transitionState == TransitionState::TRANSITION_NONE) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
        
        DrawTextureNPatch(*GameOver,
                    NPatchInfo{Rectangle{0, 0, (float)(*GameOver).width,
                                        (float)(*GameOver).height}, 0, 0, 0, 0},
                    Rectangle{(float)GetScreenWidth() / 2 - 320, (float)GetScreenHeight() / 2 - 150, 640, 128}, Vector2{0, 0}, 0.0f, WHITE);
        DrawTextEx(*SuperMarioFont, "Press Enter To Restart",
                       Vector2{(float)GetScreenWidth() / 2 - MeasureTextEx(
                        *SuperMarioFont,
                        "Press Enter To Restart",
                        30,7).x/2,
                        (float)GetScreenHeight() / 2 +150}, 
                       30, 7, Color{248,248,0,255});
    }
    if(currentLevel->getState() == LevelState::LEVEL_STATE_NEED_RESET && transitionState == TransitionState::TRANSITION_NONE){
        DrawTextEx(*SuperMarioFont, "Press Any Key To Reset Level",
                       Vector2{(float)GetScreenWidth() / 2 - MeasureTextEx(
                        *SuperMarioFont,
                        "Press Any Key To Reset Level",
                        30,7).x/2,
                        (float)GetScreenHeight() / 2 -200}, 
                       30, 7, Color{248,248,0,255});
    }
    switch(transitionState){
        case TransitionState::TRANSITION_NEXT_LEVEL:
        {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
        
        DrawTextEx(*SuperMarioFont, ("Level " + std::to_string(currentLevelID )).c_str(),
        Vector2{(float)GetScreenWidth() / 2 - MeasureTextEx(
         *SuperMarioFont,
         ("Level " + std::to_string(currentLevelID )).c_str(),
         20,7).x/2,
         (float)GetScreenHeight() / 2 -100}, 
        20, 7, WHITE);
        if(selectedCharacterType == CharacterType::MARIO) {
            DrawTextureNPatch(*SmallMario,
                       NPatchInfo{Rectangle{0, 0, (float)(*SmallMario).width,
                                           24}, 0, 0, 0, 0},
                       Rectangle{(float)GetScreenWidth() / 2 -100, (float)GetScreenHeight() / 2-16, 43, 32}, Vector2{0, 0}, 0.0f, WHITE);
        } else if(selectedCharacterType == CharacterType::LUIGI) {
            DrawTextureNPatch(*SmallLuigi,
                       NPatchInfo{Rectangle{0, 0, (float)(*SmallLuigi).width,
                                           24}, 0, 0, 0, 0},
                       Rectangle{(float)GetScreenWidth() / 2 -100, (float)GetScreenHeight() / 2-16, 43, 32}, Vector2{0, 0}, 0.0f, WHITE);
        }
        
        Vector2 size = MeasureTextEx(*SuperMarioFont,
            ("X " + std::to_string(currentLevelID + 1)).c_str(), 20, 7);

        DrawTextEx(*SuperMarioFont, ("X " + std::to_string(playerMemento->getLives())).c_str(),
        Vector2{(float)GetScreenWidth() / 2 -size.x/2,
         (float)GetScreenHeight() / 2-size.y/2 }, 
        20, 7, WHITE);
            break;
        }
        case TransitionState::TRANSITION_LEVEL_RESET:
        {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
        
            DrawTextEx(*SuperMarioFont, ("Level " + std::to_string(currentLevelID )).c_str(),
            Vector2{(float)GetScreenWidth() / 2 - MeasureTextEx(
             *SuperMarioFont,
             ("Level " + std::to_string(currentLevelID )).c_str(),
             20,7).x/2,
             (float)GetScreenHeight() / 2 -100}, 
            20, 7, WHITE);
            if(selectedCharacterType == CharacterType::MARIO) {
            DrawTextureNPatch(*SmallMario,
                           NPatchInfo{Rectangle{0, 0, (float)(*SmallMario).width,
                                               24}, 0, 0, 0, 0},
                           Rectangle{(float)GetScreenWidth() / 2 -100, (float)GetScreenHeight() / 2-16, 43, 32}, Vector2{0, 0}, 0.0f, WHITE);
            } else if(selectedCharacterType == CharacterType::LUIGI) {
            DrawTextureNPatch(*SmallLuigi,
                           NPatchInfo{Rectangle{0, 0, (float)(*SmallLuigi).width,
                                               24}, 0, 0, 0, 0},
                           Rectangle{(float)GetScreenWidth() / 2 -100, (float)GetScreenHeight() / 2-16, 43, 32}, Vector2{0, 0}, 0.0f, WHITE);
            }
            Vector2 size = MeasureTextEx(*SuperMarioFont,
                ("X " + std::to_string(currentLevelID + 1)).c_str(), 20, 7);
    
            DrawTextEx(*SuperMarioFont, ("X " + std::to_string(playerMemento->getLives())).c_str(),
            Vector2{(float)GetScreenWidth() / 2 -size.x/2,
             (float)GetScreenHeight() / 2-size.y/2 }, 
            20, 7, WHITE);
                break;
            }
        case TransitionState::TRANSITION_GAME_OVER:
        {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
        
            DrawTextEx(*SuperMarioFont, ("Level " + std::to_string(currentLevelID )).c_str(),
            Vector2{(float)GetScreenWidth() / 2 - MeasureTextEx(
             *SuperMarioFont,
             ("Level " + std::to_string(currentLevelID )).c_str(),
             20,7).x/2,
             (float)GetScreenHeight() / 2 -100}, 
            20, 7, WHITE);
    
            if(selectedCharacterType == CharacterType::MARIO) {
            DrawTextureNPatch(*SmallMario,
                       NPatchInfo{Rectangle{0, 0, (float)(*SmallMario).width,
                                           24}, 0, 0, 0, 0},
                       Rectangle{(float)GetScreenWidth() / 2 -100, (float)GetScreenHeight() / 2-16, 43, 32}, Vector2{0, 0}, 0.0f, WHITE);
        } else if(selectedCharacterType == CharacterType::LUIGI) {
            DrawTextureNPatch(*SmallLuigi,
                       NPatchInfo{Rectangle{0, 0, (float)(*SmallLuigi).width,
                                           24}, 0, 0, 0, 0},
                       Rectangle{(float)GetScreenWidth() / 2 -100, (float)GetScreenHeight() / 2-16, 43, 32}, Vector2{0, 0}, 0.0f, WHITE);
        }               
            Vector2 size = MeasureTextEx(*SuperMarioFont,
                ("X " + std::to_string(currentLevelID + 1)).c_str(), 20, 7);
    
            DrawTextEx(*SuperMarioFont, ("X " + std::to_string(playerMemento->getLives())).c_str(),
            Vector2{(float)GetScreenWidth() / 2 -size.x/2,
             (float)GetScreenHeight() / 2-size.y/2 }, 
            20, 7, WHITE);
                break;
    }
}
    menuButton.Draw();
   
}