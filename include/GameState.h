#pragma once
#include "StateManager.h"
#include "Level.h"
#include "Button.h"
#include "HUD.h"
#include <memory>
class Level;
//GameState to manage levels and its transitions, with HUD and Buttons
// enum class GAME_STATE_EVENT {
//     GAME_STATE_EVENT_TRANSITION_TO_NEXT_LEVEL,
//     GAME_STATE_EVENT_RESETING_LEVEL,

// };
class GameState : public State {
private:
    HUD gameHUD;
    Button menuButton;


    std::unique_ptr<Level> currentLevel;
    std::unique_ptr<PlayerData> playerMemento;

    int currentLevelID;

    // void Exit() override;
    void nextLevel();

public:
    GameState(StateManager *manager);
    ~GameState();

    HUD& getHUD() { return gameHUD; }

    void resetLevelWhenMarioDead();
    void drawLevelEndSummary();

    void update() override;
    void draw() override;
};