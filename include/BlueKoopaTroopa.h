#ifndef BLUE_KOOPA_TROOPA_H
#define BLUE_KOOPA_TROOPA_H

#include "../include/Monster.h"
#include "../include/Tile.h"

class BlueKoopaTroopa : public Monster {
public:
    BlueKoopaTroopa(Vector2 pos, float speed);
    virtual void updateStateAndPhysic() override;
    virtual void handleCollision(const Tile& tile, CollisionInfo type) override;
    virtual void Draw() override;
    void updateSprite();

private:
    bool isTileBelowAhead(const std::vector<Tile*>& tiles);
};

#endif