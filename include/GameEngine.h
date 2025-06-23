#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "World.h"
#include "raylib.h"
#include "Goomba.h"
#include "Monster.h"
#include "BlueKoopaTroopa.h"
#include "PiranhaPlant.h"
#include "FlyingGoomba.h"

class GameEngine {
public:
    GameEngine(int width, int height);
    ~GameEngine();
    void update();
    void draw();
    void run();
private:
    int screenWidth;
    int screenHeight;
    bool isPaused;
    bool isGameOver;
    float startDelay;
    World* world;
    Mario* player;
    void spawnMonsters();
};
#endif