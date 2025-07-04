#pragma once
#include "Entity.h"
#include "Mario.h"
#include "CollisionInfo.h"
#include "Tile.h"
#include "Coin.h"
#include "Mushroom.h"
#include "1UpMushroom.h"
#include "FireFlower.h"
#include "Star.h"
#include "3UpMoon.h"
class HUD;

class CollisionMediator {
    private:
    void HandleMarioWithTile(Mario*& mario, Tile* &tile, CollisionInfo AtoB);
    void HandleFireballWithTile(Fireball*& fireball, Tile*& tile, CollisionInfo AtoB);
    void HandleMarioWithCoin(Mario*& mario, Coin*& coin, CollisionInfo AtoB);
	void HandleMarioWithMushroom(Mario*& mario, Mushroom*& mushroom, CollisionInfo AtoB);
	void HandleItemWithTile(Item*& item, Tile*& tile, CollisionInfo AtoB);
    void HandleMarioWith1UpMushroom(Mario*& mario, UpMushroom*& mushroom, CollisionInfo AtoB);
    void HandleMarioWithItem(Mario*& mario, Item*& item, CollisionInfo AtoB);

    public:
    void HandleCollision(Entity* entityA, Entity* entityB);
    
};
