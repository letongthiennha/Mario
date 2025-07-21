#pragma once

#include "Monster.h"

class BanzaiBill : public Monster {
public:
    BanzaiBill(Vector2 pos, float speed);

    void updateStateAndPhysic() override;
    void updateSprite();
    void handleCollision(const Tile& tile, CollisionInfo type) override;

private:
    float frameTime;
    float frameAcum;
    int maxFrame;
    int currFrame;


};
