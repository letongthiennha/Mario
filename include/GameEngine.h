/* File: ../include/GameEngine.h */
#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "raylib.h"
#include "Mario.h"
#include "World.h"
#include "ResourceManager.h"
#include "GameClock.h"
#include "Monster.h"
#include "Goomba.h"
#include <vector>

class GameEngine {
private:
    World* world;
    Mario* player;
    std::vector<Monster*> monsters;
    bool isPaused;
    bool isGameOver;
    int screenWidth;
    int screenHeight;
    float startDelay; // Delay for initial collision checks
public:
    GameEngine(int width, int height);
    ~GameEngine();
    void spawnMonsters();
    void update();
    void draw();
    void run();
};

#endif // GAMEENGINE_H