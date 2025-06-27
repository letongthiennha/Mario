#pragma once
#include "raylib.h"
#include "GameClock.h"
#include "Tile.h"
#include <vector>
#include "Mario.h"
#include"Map.h"     
#include "CollisionMediator.h"
#include "GameState.h"
class GameState;
//Physical level of the game, contains the gameplay
class Level
{   
private:
    float currBackgroundStarX=0.0f;
    Texture2D background;
    Color backgroundColor;
    Map map;
    CollisionMediator collisionMediator;
    Mario player;
    std::vector<Tile *> &interactiveTiles;
    Camera2D camera;
    GameState *gameState;
    bool isCompleted = false;
public:
    Level(int mapNumber,GameState* gameState);
    ~Level();
    bool IsCompleted();
    void UpdateLevel();
    void DrawLevel();
    static  constexpr float GRAVITY=1800;
    static void InitWorld();

};