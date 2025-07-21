#ifndef BLUE_KOOPA_TROOPA_H
#define BLUE_KOOPA_TROOPA_H

#include "Monster.h"
#include "Tile.h"

class KoopaTroopa : public Monster {
public:
    KoopaTroopa(Vector2 pos, float speed);
    virtual void updateStateAndPhysic() override;
    virtual void handleCollision(const Tile& tile, CollisionInfo type) override;
    void updateSprite();

private:
    bool isTileBelowAhead(const std::vector<Tile*>& tiles);
};

#endif