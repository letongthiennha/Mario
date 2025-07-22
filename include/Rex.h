#pragma once
#include "Monster.h"

class Rex : public Monster {
public:
    Rex(Vector2 pos, float speed);
    void updateSprite() override;
    void updateStateAndPhysic() override;
    void handleCollision(const Tile& tile, CollisionInfo type) override;

private:
    int hitsToDie = 2;
    float dyingFrameAcum = 0;
    float dyingFrameTime = 0.1f;
    int currentDyingFrame = 0;
    const int maxDyingFrames = 4;
    Vector2 posOnDying;
};