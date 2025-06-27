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
    std::string summarry="END OF LEVEL";
    HUD gameHUD;

public:
    GameState(StateManager *manager);
    ~GameState();
    HUD& getHUD() { return gameHUD; }
    // void Enter() override;
    void onLevelEnd();
    void update() override;
    void draw() override;
};