#pragma once
#include "StateManager.h"
#include "Level.h"
#include "Button.h"
#include "HUD.h"
#include <memory>
class Level;
class GameState : public State {
private:
    std::unique_ptr<Level> currentLevel;
    Button menuButton;
    int currentLevelID;
    // void Exit() override;
    void nextLevel();
    HUD gameHUD;
    int score;

public:
    GameState(StateManager *manager);
    ~GameState();
    HUD& getHUD() { return gameHUD; }
    // void Enter() override;
    void updateOnlevelEnd();
    void drawLevelEndSummary();
    void update() override;
    void draw() override;
};