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
#include "Monster.h"
class HUD;
class Monster;
class CollisionMediator {
    private:
    void HandleMarioWithTile(Mario*& mario, Tile* &tile, CollisionInfo AtoB);
    void HandleMarioWithMonster(Mario*& mario, Monster*& monster, CollisionInfo AtoB);
    void HandleMarioWithItem(Mario*& mario, Item*& item, CollisionInfo AtoB);

    void HandleFireballWithTile(Fireball*& fireball, Tile*& tile, CollisionInfo AtoB);
    void HandleFireballWithMonster(Fireball*& fireball, Monster*& monster, CollisionInfo AtoB);
	void HandleItemWithTile(Item*& item, Tile*& tile, CollisionInfo AtoB);
    void HandleMonsterWithTile(Monster*& monster, Tile*& tile, CollisionInfo AtoB);
    public:
    void HandleCollision(Entity* entityA, Entity* entityB);
    
};
