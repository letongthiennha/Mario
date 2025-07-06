#ifndef PIRANHA_PLANT_H
#define PIRANHA_PLANT_H

#include "Monster.h"
#include "Tile.h"

class PiranhaPlant : public Monster {
private:
    float minY, maxY;
    float animVel;
    float waitAcum, waitTime;
    bool waiting;

public:
    PiranhaPlant(Vector2 pos, float speed);
    virtual void updateStateAndPhysic() override;
    virtual void handleCollision(const Tile& tile, CollisionInfo type) override;
    virtual void Draw() override;
    void updateSprite();
};

#endif