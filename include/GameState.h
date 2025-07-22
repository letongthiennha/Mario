#pragma once
#include "StateManager.h"
#include "Level.h"
#include "Button.h"
#include "HUD.h"
#include <memory>
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

    TransitionState transitionState;
    std::unique_ptr<Level> currentLevel;
    std::unique_ptr<PlayerData> playerMemento;

    int currentLevelID;
    float transitionTime;
    float transitionTimeAcum;
    // void Exit() override;
    void nextLevel();

public:
    GameState(StateManager *manager);
    ~GameState();

    HUD& getHUD() { return gameHUD; }

    void resetLevelWhenPlayerDead();
    void drawLevelEndSummary();
    void resetwhenGameOver();
    void startTransition(TransitionState state);
    
    void update() override;
    void draw() override;
};