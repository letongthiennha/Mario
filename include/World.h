/* File: ../include/World.h */
#ifndef WORLD_H
#define WORLD_H
#include "raylib.h"
#include "GameClock.h"
#include "Tile.h"
#include <vector>
#include "Mario.h"

class World {   
private:
    static float GRAVITY;
    std::vector<Tile*> interactiveTiles;
    Mario player;
    Camera2D camera;
public:
    World();
    ~World();
    void UpdateWorld();
    void DrawWorld();
    static const float GetGravity();
    static void InitWorld();
    Mario& getPlayer(); // Getter for player
    std::vector<Tile*>& getInteractiveTiles(); // Getter for interactiveTiles
};

#endif // WORLD_H