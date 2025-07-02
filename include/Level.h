#pragma once
#include "raylib.h"
#include "GameClock.h"
#include "Tile.h"
#include <vector>
#include "Mario.h"
#include"Map.h"     
#include "CollisionMediator.h"
#include "GameState.h"
#include "LevelState.h"
class GameState;
//Physical level of the game, contains the gameplay

class Level
{   
private:
    float currBackgroundStarX=0.0f;
    Texture2D background;
    Color backgroundColor;
    Map map;

    Mario player;
    Vector2 startPositionforPlayer;

    std::vector<Tile *> &interactiveTiles;
    CollisionMediator collisionMediator;

    Camera2D camera;    
    GameState *gameState;
    LevelState state;

public:
    Level(int mapNumber,GameState* gameState,const PlayerData& PlayerData);
    LevelState getState() const;
    bool needReset() const;
    ~Level();
    std::unique_ptr<PlayerData> getPlayerData();
    bool IsCompleted() ;
    void UpdateLevel();
    void DrawLevel();
    static  constexpr float GRAVITY=1800;
};