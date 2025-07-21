#ifndef GOOMBA_H
#define GOOMBA_H
#include "Monster.h"
#include "Tile.h"
#include "ResourceManager.h"

class Goomba : public Monster {
public:
    Goomba(Vector2 pos, float speed);
    void updateStateAndPhysic();
    bool isTileBelowAhead(const std::vector<Tile*>& tiles);
    void handleCollision(const Tile &tile, CollisionInfo type) override {};

private:
    void updateSprite();
};

#endif