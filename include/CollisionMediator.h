#pragma once
#include "Entity.h"
#include "Mario.h"
#include "CollisionInfo.h"
#include "Tile.h"
class HUD;

class CollisionMediator {
    private:
    void HandleMarioWithTile(Mario*& mario, Tile* &tile, CollisionInfo AtoB);
    void HandleFireballWithTile(Fireball*& fireball, Tile*& tile, CollisionInfo AtoB);
    public:
    void HandleCollision(Entity* entityA, Entity* entityB);

};
