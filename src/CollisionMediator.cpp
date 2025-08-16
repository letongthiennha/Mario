#include "CollisionMediator.h"
#include "SoundController.h"
#include "CourseClearToken.h"
#include "QUestionBlock.h"
#include "BanzaiBill.h"
#include "Rex.h"
void CollisionMediator::HandlePlayerWithTile(PlayableCharacter *& Player, Tile * &tile, CollisionInfo AtoB)
{
    if(Player->getState()==ENTITY_STATE_DYING||Player->getState()==ENTITY_STATE_TO_BE_REMOVED||Player->getState()==ENTITY_STATE_VICTORY_DANCE)
        return;
    if (AtoB == COLLISION_NONE)
        return;

    switch (AtoB)
    {
        
        case COLLISION_SOUTH:
        {
            if(Player->getState()==ENTITY_STATE_JUMPING)
                return;
            Player->setPosition(Vector2{Player->getPosition().x, tile->getPosition().y - Player->getSize().y});
            Player->setState(ENTITY_STATE_ON_GROUND);
            Player->setVelocity(Vector2{Player->getVelocity().x, 0});
            break;
        }
        
        case COLLISION_NORTH:
        {
            Player->setPosition(Vector2{Player->getPosition().x, tile->getPosition().y + tile->getSize().y});
            Player->setVelocity(Vector2{Player->getVelocity().x, 0});
            break;
        }

        case COLLISION_EAST:
        {
            if(Player->getFacingDirection()==DIRECTION_LEFT)
                return;
            Player->setPosition(Vector2{tile->getPosition().x - Player->getSize().x, Player->getPosition().y});
            Player->setVelocity(Vector2{0, Player->getVelocity().y}); // Reverse the x velocity
            break;
        }
        
        case COLLISION_WEST:
        {
            if(Player->getFacingDirection()==DIRECTION_RIGHT)
                return;
            Player->setPosition(Vector2{tile->getPosition().x + tile->getSize().x, Player->getPosition().y});
            Player->setVelocity(Vector2{0, Player->getVelocity().y}); // Reverse the x velocity
            break;
        }
        default:
            break;
    }
}
void CollisionMediator::HandlePlayerWithMonster(PlayableCharacter *&Player, Monster *&monster, CollisionInfo AtoB)
{if (Player->getState() == ENTITY_STATE_DYING || 
    Player->getState() == ENTITY_STATE_TO_BE_REMOVED || 
    Player->getState() == ENTITY_STATE_VICTORY_DANCE)
    return;

if (AtoB == COLLISION_NONE)
    return;

// // ✅ BanzaiBill always kills PlayableCharacter
// if (monster->isLethalToPlayer()) {
//     Player->reactOnBeingHit();
//     return;
// }

switch (AtoB)
{
case COLLISION_SOUTH:
    if (Player->getVelocity().y > 0) // PlayableCharacter is jumping down
    {
        Player->addScore(400); // Add score for defeating the monster

        
        monster->onHit();
        Player->setVelocity(Vector2{Player->getVelocity().x, -600}); // Bounce effect
        SoundController::getInstance().PlaySound("MARIO_STOMP");
    }
    break;
default:
        Player->reactOnBeingHit();
    break;
}
}
void CollisionMediator::HandleFireballWithTile(Fireball *&fireball, Tile *&tile, CollisionInfo AtoB)
{
    if (AtoB == COLLISION_NONE)
        return;
    switch (AtoB)
    {
    case COLLISION_SOUTH:
    {
        fireball->setPosition(Vector2{fireball->getPosition().x, tile->getPosition().y - fireball->getSize().y});
        fireball->setVelocity(Vector2{fireball->getVelocity().x, -500});
        break;
    }
    case COLLISION_NORTH:
    {
        fireball->setPosition(Vector2{fireball->getPosition().x, tile->getPosition().y + tile->getSize().y});
        fireball->setVelocity(Vector2{fireball->getVelocity().x, 0});
        break;
    }
    case COLLISION_EAST:
    {
        fireball->setPosition(Vector2{tile->getPosition().x - fireball->getSize().x, fireball->getPosition().y});
        fireball->setVelocity(Vector2{-fireball->getVelocity().x, fireball->getVelocity().y}); // Reverse the x velocity
        if (fireball->getCurrFrame() == 0)
        {
            fireball->setCurrFrame(3);
        }
        else
            fireball->setCurrFrame(fireball->getCurrFrame() - 1);
        break;
    }
    case COLLISION_WEST:
    {
        fireball->setPosition(Vector2{tile->getPosition().x + fireball->getSize().x + tile->getSize().x, fireball->getPosition().y});
        fireball->setVelocity(Vector2{-fireball->getVelocity().x, fireball->getVelocity().y}); // Reverse the x velocity
        if (fireball->getCurrFrame() == 0)
        {
            fireball->setCurrFrame(3);
        }
        else
            fireball->setCurrFrame(fireball->getCurrFrame() - 1);
        break;
    }
    }
}

void CollisionMediator::HandleFireballWithMonster(Fireball *&fireball, Monster *&monster, CollisionInfo AtoB)
{
    if (AtoB == COLLISION_NONE)
        return;
    if (monster->getState() == ENTITY_STATE_DYING || monster->getState() == ENTITY_STATE_TO_BE_REMOVED||monster->getIsActive() == false)
        return;
    monster->onHit(); // Monster dies when hit by a fireball
    fireball->setState(ENTITY_STATE_TO_BE_REMOVED); // Fireball is removed after hitting a monster
    SoundController::getInstance().PlaySound("MARIO_STOMP");
}

void CollisionMediator::HandleFireballWithBlock(Fireball *&fireball, Block *&block, CollisionInfo AtoB)
{
    if (AtoB == COLLISION_NONE)
        return;

    switch (AtoB)
    {
    case COLLISION_SOUTH:
    {
        fireball->setPosition(Vector2{fireball->getPosition().x, block->getPosition().y - fireball->getSize().y});
        fireball->setVelocity(Vector2{fireball->getVelocity().x, -500});
        break;
    }
    case COLLISION_NORTH:
    {
        fireball->setPosition(Vector2{fireball->getPosition().x, block->getPosition().y + block->getSize().y});
        fireball->setVelocity(Vector2{fireball->getVelocity().x, 0});
        break;
    }
    case COLLISION_EAST:
    {
        fireball->setPosition(Vector2{block->getPosition().x - fireball->getSize().x, fireball->getPosition().y});
        fireball->setVelocity(Vector2{-fireball->getVelocity().x, fireball->getVelocity().y}); // Reverse the x velocity
        if (fireball->getCurrFrame() == 0)
        {
            fireball->setCurrFrame(3);
        }
        else
            fireball->setCurrFrame(fireball->getCurrFrame() - 1);
        break;
    }
    case COLLISION_WEST:
    {
        fireball->setPosition(Vector2{block->getPosition().x + block->getSize().x + fireball->getSize().x, fireball->getPosition().y});
        fireball->setVelocity(Vector2{-fireball->getVelocity().x, fireball->getVelocity().y}); // Reverse the x velocity
        if (fireball->getCurrFrame() == 0)
        {
            fireball->setCurrFrame(3);
        }
        else
            fireball->setCurrFrame(fireball->getCurrFrame() - 1);
        break;
    }
    }
}

void CollisionMediator::HandleCollision(Entity *entityA, Entity *entityB)

{

    PlayableCharacter* isAPlayer = dynamic_cast<PlayableCharacter*>(entityA);
    PlayableCharacter* isBPlayer = dynamic_cast<PlayableCharacter*>(entityB);
    Fireball* isAfireball = dynamic_cast<Fireball*>(entityA);
    Fireball* isBfireball = dynamic_cast<Fireball*>(entityB);
    Tile* isAtile = dynamic_cast<Tile*>(entityA);
    Tile* isBtile = dynamic_cast<Tile*>(entityB);
    Item* isAitem = dynamic_cast<Item*>(entityA);
    Item* isBitem = dynamic_cast<Item*>(entityB);
    Monster* isAmonster = dynamic_cast<Monster*>(entityA);
    Monster* isBmonster = dynamic_cast<Monster*>(entityB);
    Block* isAblock = dynamic_cast<Block*>(entityA);
    Block* isBblock = dynamic_cast<Block*>(entityB);
    if (isAPlayer && isBtile|| isBPlayer&& isAtile)
    {
        CollisionInfo AtoB = isAPlayer ? isAPlayer->CheckCollisionType(*isBtile) : isBPlayer->CheckCollisionType(*isAtile);
        if (isAPlayer)
            HandlePlayerWithTile(isAPlayer, isBtile, AtoB);
        else
            HandlePlayerWithTile(isBPlayer, isAtile, AtoB);
    }
    else if (isAfireball && isBtile || isBfireball && isAtile)
    {
        CollisionInfo AtoB = isAfireball ? isAfireball->CheckCollisionType(*isBtile) : isBfireball->CheckCollisionType(*isAtile);
        if (isAfireball)
            HandleFireballWithTile(isAfireball, isBtile, AtoB);
        else
            HandleFireballWithTile(isBfireball, isAtile, AtoB);
    }
    else if(isAPlayer && isBitem || isBPlayer && isAitem)
    {
        PlayableCharacter* Player = isAPlayer ? isAPlayer : isBPlayer;
        Item* item = isAitem ? isAitem : isBitem;
        CollisionInfo AtoB = Player->CheckCollisionType(*item);
        HandlePlayerWithItem(Player, item, AtoB);
	}
    else if (isAitem && isBtile || isBitem && isAtile)
    {
        Item* item = isAitem ? isAitem : isBitem;
        Tile* tile = isAtile ? isAtile : isBtile;
        CollisionInfo AtoB = item->CheckCollisionType(*tile);
        HandleItemWithTile(item, tile, AtoB);
    }
    else if (isAmonster && isBtile || isBmonster && isAtile)
    {
        Monster* monster = isAmonster ? isAmonster : isBmonster;
        Tile* tile = isAtile ? isAtile : isBtile;
        CollisionInfo AtoB = monster->CheckCollisionType(*tile);
        HandleMonsterWithTile(monster, tile, AtoB);
    }

    else if (isAPlayer && isBmonster || isBPlayer && isAmonster)
    {
        PlayableCharacter* Player = isAPlayer ? isAPlayer : isBPlayer;
        Monster* monster = isAmonster ? isAmonster : isBmonster;

        CollisionInfo AtoB = Player->CheckCollisionType(*monster);
        HandlePlayerWithMonster(Player, monster, AtoB);
    }
    
    else if (isAfireball && isBmonster || isBfireball && isAmonster)
    {
        Fireball* fireball = isAfireball ? isAfireball : isBfireball;
        Monster* monster = isAmonster ? isAmonster : isBmonster;
        CollisionInfo AtoB = fireball->CheckCollisionType(*monster);
        HandleFireballWithMonster(fireball, monster, AtoB);
    }
    else if( isAPlayer && isBblock || isBPlayer && isAblock)
    {
        PlayableCharacter* Player = isAPlayer ? isAPlayer : isBPlayer;
        Block* block = isAblock ? isAblock : isBblock;
        CollisionInfo AtoB = Player->CheckCollisionType(*block);
        HandlePlayerWithBlock(Player, block, AtoB);
    }
    else if (isAmonster && isAblock || isBmonster && isBblock)
    {
        Monster* monster = isAmonster ? isAmonster : isBmonster;
        Block* block = isAblock ? isAblock : isBblock;
        CollisionInfo AtoB = monster->CheckCollisionType(*block);
        HandleMonsterWithBlock(monster, block, AtoB);
    }
    else if (isAfireball && isBblock || isBfireball && isAblock)
    {
        Fireball* fireball = isAfireball ? isAfireball : isBfireball;
        Block* block = isAblock ? isAblock : isBblock;
        CollisionInfo AtoB = fireball->CheckCollisionType(*block);
        HandleFireballWithBlock(fireball, block, AtoB);
    }
    else if (isAitem && isBblock || isBitem && isAblock)
    {
        Item* item = isAitem ? isAitem : isBitem;
        Block* block = isAblock ? isAblock : isBblock;
        CollisionInfo AtoB = item->CheckCollisionType(*block);
        HandleItemWithBlock(item, block, AtoB);
    }
}

void CollisionMediator::HandlePlayerWithItem(PlayableCharacter*& Player, Item*& item, CollisionInfo AtoB) {
    if (AtoB == COLLISION_NONE)
        return;

    if (AtoB == COLLISION_NORTH && item->getState() == ItemState::UNACTIVE) {
		item->setState(ItemState::POP_UP);
    }

    if (item&&item->getState() != ItemState::IDLE)
        return;

    if (item&&CheckCollisionRecs(Player->getRect(), item->getRect())) {
        if (auto* coin = dynamic_cast<Coin*>(item)) {
            coin->collect();
            Player->addCoin(1);
            Player->addScore(200); // Add score for collecting a coin
        }
        else if (auto* upMushroom = dynamic_cast<UpMushroom*>(item)) {
            upMushroom->collect();
            // Increase PlayableCharacter's life by 1
            Player->addLives(1);
            Player ->addScore(1000); // Add score for collecting a 1-Up mushroom
        }
        else if (auto* mushroom = dynamic_cast<Mushroom*>(item)) {
            mushroom->collect();
            if(Player->getForm() == PLAYER_STATE_SMALL)
            Player->startTransformingSmallToBig();
             Player->addScore(1000); // If PlayableCharacter is already big or fire, just add score
        }
        else if(auto* fireFlower= dynamic_cast<FireFlower*>(item)) {
            fireFlower->collect();
            if(Player->getForm() == PLAYER_STATE_BIG)
            Player->startTransformingBigToFire();
            else if(Player->getForm() == PLAYER_STATE_SMALL)
            Player->startTransformingSmallToFire();
             Player->addScore(1000); // If PlayableCharacter is already fire, just add score
        }
        else if(auto* star= dynamic_cast<Star*>(item)) {
            star->collect();
            Player->addScore(1000);
			// change to invincible state
        }
        else if (auto* upMoon = dynamic_cast<UpMoon*>(item)) {
            upMoon->collect();
			// Increase PlayableCharacter's life by 3
            Player->addLives(3);
            Player->addScore(3000); // Add score for collecting a 3-Up moon
        }
        else if (auto* clearToken = dynamic_cast<ClearToken*>(item)) {
			clearToken->collect();
            Player->changeWinState(true);
        }
        else {
            // Handle other items if needed
            return;
        }
        // .... other items
    }
}

void CollisionMediator::HandlePlayerWithBlock(PlayableCharacter *&Player, Block *&block, CollisionInfo AtoB)
{
    if (AtoB == COLLISION_NONE)
        return;

    if (Player->getState() == ENTITY_STATE_DYING || Player->getState() == ENTITY_STATE_TO_BE_REMOVED || Player->getState() == ENTITY_STATE_VICTORY_DANCE)
        return;

    switch (AtoB) {
        case COLLISION_SOUTH:
            if(Player->getState()==ENTITY_STATE_JUMPING)
                return;
            Player->setPosition({Player->getPosition().x, block->getPosition().y - Player->getSize().y});
            Player->setVelocity({Player->getVelocity().x, 0});
            Player->setState(ENTITY_STATE_ON_GROUND);
            break;
        case COLLISION_NORTH:
            Player->setPosition({Player->getPosition().x, block->getPosition().y + block->getSize().y});
            Player->setVelocity({Player->getVelocity().x, 0});
            if(dynamic_cast<QuestionBlock*>(block)) {
                QuestionBlock* questionBlock = dynamic_cast<QuestionBlock*>(block);
                questionBlock->ActiveReward();
            }
            break;
        case COLLISION_EAST:
            if(Player->getFacingDirection()==DIRECTION_LEFT) return;
            Player->setPosition({block->getPosition().x - Player->getSize().x, Player->getPosition().y});
            Player->setVelocity({0, Player->getVelocity().y});
            break;
        case COLLISION_WEST:
            if(Player->getFacingDirection()==DIRECTION_RIGHT) return;
            Player->setPosition({block->getPosition().x + block->getSize().x, Player->getPosition().y});
            Player->setVelocity({0, Player->getVelocity().y});
            break;
        default:
            break;
    }
}

void CollisionMediator::HandleMonsterWithTile(Monster *&monster, Tile *&tile, CollisionInfo AtoB)
{
    if(monster->getState() == ENTITY_STATE_DYING || monster->getState() == ENTITY_STATE_TO_BE_REMOVED)
        return;
    if (AtoB == COLLISION_NONE)
        return;
    if (dynamic_cast<BanzaiBill*>(monster))
        return; // BanzaiBill does not collide with tiles in this way
    switch (AtoB) {
                case COLLISION_SOUTH:
                    monster->setPosition({monster->getPosition().x, tile->getPosition().y - monster->getSize().y});
                    monster->setVelocity({monster->getVelocity().x, 0});
                    monster->setState(ENTITY_STATE_ON_GROUND);
                    break;
                case COLLISION_EAST:
                    monster->setPosition({tile->getPosition().x - monster->getSize().x, monster->getPosition().y});
                    if(monster->getVelocity().x > 0)  monster->setVelocity({-monster->getVelocity().x, monster->getVelocity().y}); // Reverse the x velocity
                    break;
                case COLLISION_WEST:
                    monster->setPosition({tile->getPosition().x + tile->getSize().x, monster->getPosition().y});
                    if(monster->getVelocity().x < 0)  monster->setVelocity({-monster->getVelocity().x, monster->getVelocity().y}); // Reverse the x velocity
                    break;
                case COLLISION_NORTH:
                    monster->setPosition({monster->getPosition().x, tile->getPosition().y + tile->getSize().y});
                    monster->setVelocity({monster->getVelocity().x, 0});
                    break;
                default:
                    break;
    }
}

void CollisionMediator::HandleMonsterWithBlock(Monster *&monster, Block *&block, CollisionInfo AtoB)
{
    if (AtoB == COLLISION_NONE)
        return;
    if(dynamic_cast<BanzaiBill*> (monster))
        return;
    if (monster->getState() == ENTITY_STATE_DYING || monster->getState() == ENTITY_STATE_TO_BE_REMOVED)
        return;

    switch (AtoB) {
        case COLLISION_SOUTH:
            monster->setPosition({monster->getPosition().x, block->getPosition().y - monster->getSize().y});
            monster->setVelocity({monster->getVelocity().x, 0});
            monster->setState(ENTITY_STATE_ON_GROUND);
            break;
        case COLLISION_NORTH:
            monster->setPosition({monster->getPosition().x, block->getPosition().y + block->getSize().y});
            monster->setVelocity({monster->getVelocity().x, 0});
            break;
        case COLLISION_EAST:
            if(monster->getFacingDirection() == DIRECTION_LEFT) return;
            monster->setPosition({block->getPosition().x - monster->getSize().x, monster->getPosition().y});
            monster->setVelocity({-monster->getVelocity().x, monster->getVelocity().y}); // Reverse the x velocity
            monster->setFacingDirection(DIRECTION_LEFT);
            break;
        case COLLISION_WEST:
            if(monster->getFacingDirection() == DIRECTION_RIGHT) return;
            monster->setPosition({block->getPosition().x + block->getSize().x, monster->getPosition().y});
            monster->setVelocity({-monster->getVelocity().x, monster->getVelocity().y}); // Reverse the x velocity
            monster->setFacingDirection(DIRECTION_RIGHT);
            break;
        default:
            break;
    }
}

void CollisionMediator::HandleItemWithTile(Item*& item, Tile*& tile, CollisionInfo AtoB)
{
    if (AtoB == COLLISION_NONE || dynamic_cast<ClearToken*>(item) != nullptr)
        return;

    if (item->getState() == ItemState::POP_UP||item->getState() == ItemState::UNACTIVE)
        return;

    Vector2 velocity = item->getVelocity();
    Vector2 position = item->getPosition();

    switch (AtoB)
    {
    case COLLISION_SOUTH:
        position.y = tile->getPosition().y - item->getSize().y;
        if (dynamic_cast<Star*>(item) == nullptr) {
            velocity.y = 0;
        }
        item->setOnGround(true);
        break;
    case COLLISION_NORTH:
        position.y = tile->getPosition().y + tile->getSize().y;
        velocity.y = 0;
        break;
    case COLLISION_EAST:
        position.x = tile->getPosition().x - item->getSize().x;
        velocity.x = -velocity.x; // Reverse direction
		break;
    case COLLISION_WEST:
		position.x = tile->getPosition().x + tile->getSize().x;
        velocity.x = -velocity.x; // Reverse direction
        break;
    default:
        break;
    }

    if (AtoB != COLLISION_SOUTH) {
        item->setOnGround(false);
    }

    item->setPosition(position);
    item->setVelocity(velocity);
}

void CollisionMediator::HandleItemWithBlock(Item *&item, Block *&block, CollisionInfo AtoB)
{
    if (AtoB == COLLISION_NONE)
        return;

    if (item->getState() == ItemState::POP_UP || item->getState() == ItemState::UNACTIVE)
        return;

    Vector2 velocity = item->getVelocity();
    Vector2 position = item->getPosition();

    switch (AtoB)
    {
    case COLLISION_SOUTH:
        position.y = block->getPosition().y - item->getSize().y;
        if (dynamic_cast<Star*>(item) == nullptr) {
            velocity.y = 0;
        }
        item->setOnGround(true);
        break;
    case COLLISION_NORTH:
        position.y = block->getPosition().y + block->getSize().y;
        velocity.y = 0;
        break;
    case COLLISION_EAST:
        position.x = block->getPosition().x - item->getSize().x;
        velocity.x = -velocity.x; // Reverse direction
        break;
    case COLLISION_WEST:
        position.x = block->getPosition().x + block->getSize().x;
        velocity.x = -velocity.x; // Reverse direction
        break;
    default:
        break;
    }

    if (AtoB != COLLISION_SOUTH) {
        item->setOnGround(false);
    }

    item->setPosition(position);
    item->setVelocity(velocity);
}
