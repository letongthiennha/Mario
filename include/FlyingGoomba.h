#pragma once
#include "Monster.h"

class FlyingGoomba : public Monster {
private:
    float hoverRange;
    float hoverSpeed;
    float originalY;
    int hoverDirection; // 1: down, -1: up

public:
    FlyingGoomba(Vector2 pos, float speed);
    void updateSprite() override;
    void updateStateAndPhysic() override;
    void handleCollision(const Tile& tile, CollisionInfo type) override;
    void Draw() override;
};
