/* File: ../include/Goomba.h */
#ifndef GOOMBA_H
#define GOOMBA_H
#include "Monster.h"
#include "ResourceManager.h"
#include "Tile.h"

class Goomba : public Monster {
private:
    void updateSprite();
public:
    Goomba(Vector2 pos, float speed = 200.0f);
    void updateStateAndPhysic() override;
    void handleCollision(const Tile& tile, CollisionInfo type);
    void Draw() override;
};

#endif // GOOMBA_H