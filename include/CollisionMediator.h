#pragma once
#include "Entity.h"
#include "PlayableCharacter.h"
#include "CollisionInfo.h"
#include "Tile.h"
#include "Coin.h"
#include "Mushroom.h"
#include "1UpMushroom.h"
#include "FireFlower.h"
#include "Star.h"
#include "3UpMoon.h"
#include "Monster.h"
#include "Block.h"
class HUD;
class Monster;
class CollisionMediator {
    private:
    void HandlePlayerWithTile(PlayableCharacter*& Player, Tile* &tile, CollisionInfo AtoB);
    void HandlePlayerWithMonster(PlayableCharacter*& Player, Monster*& monster, CollisionInfo AtoB);
    void HandlePlayerWithItem(PlayableCharacter*& Player, Item*& item, CollisionInfo AtoB);
    void HandlePlayerWithBlock(PlayableCharacter*& Player, Block*& block, CollisionInfo AtoB);


    void HandleFireballWithTile(Fireball*& fireball, Tile*& tile, CollisionInfo AtoB);
    void HandleFireballWithMonster(Fireball*& fireball, Monster*& monster, CollisionInfo AtoB);
    void HandleFireballWithBlock(Fireball*& fireball, Block*& block, CollisionInfo AtoB);

	void HandleItemWithTile(Item*& item, Tile*& tile, CollisionInfo AtoB);
    void HandleItemWithBlock(Item*& item, Block*& block, CollisionInfo AtoB);
    
    void HandleMonsterWithTile(Monster*& monster, Tile*& tile, CollisionInfo AtoB);
    void HandleMonsterWithBlock(Monster*& monster, Block*& block, CollisionInfo AtoB);
    public:
    void HandleCollision(Entity* entityA, Entity* entityB);
    
};
