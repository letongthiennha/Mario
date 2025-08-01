#pragma once
#include "StateManager.h"
#include "Level.h"
#include "Button.h"
#include "HUD.h"
#include "CharacterType.h"
#include "ChatBotScreen.h"
#include <memory>
#include <fstream>
class Level;
// GameState to manage levels and its transitions, with HUD and Buttons
enum class TransitionState {
    TRANSITION_NEXT_LEVEL,
    TRANSITION_LEVEL_RESET,
    TRANSITION_GAME_OVER,

    TRANSITION_NONE
};
class GameState : public State {
private:
    HUD gameHUD;
    Button menuButton;
    CharacterType selectedCharacterType;

    TransitionState transitionState;
    std::unique_ptr<Level> currentLevel;
    std::unique_ptr<PlayerData> playerMemento;
    std::vector<std::unique_ptr<PlayerData>> levelMementos;

    int currentLevelID;
    float transitionTime;
    float transitionTimeAcum;
    // void Exit() override;
    void nextLevel();

    bool isChatBotOn = false;
    ChatBotScreen chatBotScreen;
    float chatToggleTimeAcum = 0.0f;
    const float CHAT_TOGGLE_COOLDOWN = 0.3f;

public:
    GameState(StateManager *manager);
    GameState(StateManager *manager, CharacterType characterType);
    ~GameState();

    HUD& getHUD() { return gameHUD; }

    void resetLevelWhenPlayerDead();
    void drawLevelEndSummary();
    void resetwhenGameOver();
    void startTransition(TransitionState state);
    void saveFinalScores();

    void saveProgress();
    
    void update() override;
    void draw() override;
};