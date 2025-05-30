#ifndef WORLD_H
#define WORLD_H
#include "Mario.h"
#include "Tile.h"
#include "raylib.h"
#include <vector>

class Monster; // Forward declaration


class World {
public:
    World();
    ~World();
    void UpdateWorld();
    void DrawWorld();
    static void InitWorld();
    static const float GetGravity();
    Mario& getPlayer();
    std::vector<Tile*>& getInteractiveTiles();
    void addMonster(Monster* monster);
    std::vector<Monster*>& getMonsters();
private:
    Mario player;
    std::vector<Tile*> interactiveTiles;
    std::vector<Monster*> monsters;
    Camera2D camera;
    static float GRAVITY;
};
#endif