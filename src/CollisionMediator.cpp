#include "CollisionMediator.h"

void CollisionMediator::HandleMarioWithTile(Mario *& mario, Tile * &tile, CollisionInfo AtoB)
{
    if (AtoB == COLLISION_NONE)
        return;

    switch (AtoB)
    {
        
        case COLLISION_SOUTH:
        {
            mario->setPosition(Vector2{mario->getPosition().x, tile->getPosition().y - mario->getSize().y});
            mario->setState(ENTITY_STATE_ON_GROUD);
            mario->setVelocity(Vector2{mario->getVelocity().x, 0});
            break;
        }
        
        case COLLISION_NORTH:
        {
            mario->setPosition(Vector2{mario->getPosition().x, tile->getPosition().y + tile->getSize().y});
            mario->setVelocity(Vector2{mario->getVelocity().x, 0});
            break;
        }

        case COLLISION_EAST:
        {
            if(mario->getFacingDirection()==DIRECTION_LEFT)
                return;
            mario->setPosition(Vector2{tile->getPosition().x - mario->getSize().x, mario->getPosition().y});
            mario->setVelocity(Vector2{0, mario->getVelocity().y}); // Reverse the x velocity
            break;
        }
        
        case COLLISION_WEST:
        {
            if(mario->getFacingDirection()==DIRECTION_RIGHT)
                return;
            mario->setPosition(Vector2{tile->getPosition().x + tile->getSize().x, mario->getPosition().y});
            mario->setVelocity(Vector2{0, mario->getVelocity().y}); // Reverse the x velocity
            break;
        }
        default:
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

void CollisionMediator::HandleMarioWithCoin(Mario*& mario, Coin*& coin, CollisionInfo AtoB)
{
    if (AtoB == COLLISION_NONE)
		return;
    if (coin->getState() != ItemState::IDLE)
        return;

    if (CheckCollisionRecs(mario->getRect(), coin->getRect())) {
        coin->collect();
    }
}

void CollisionMediator::HandleCollision(Entity *entityA, Entity *entityB)

{

    Mario* isAmario = dynamic_cast<Mario*>(entityA);
    Mario* isBmario = dynamic_cast<Mario*>(entityB);
    Fireball* isAfireball = dynamic_cast<Fireball*>(entityA);
    Fireball* isBfireball = dynamic_cast<Fireball*>(entityB);
    Tile* isAtile = dynamic_cast<Tile*>(entityA);
    Tile* isBtile = dynamic_cast<Tile*>(entityB);
	Coin* isAcoin = dynamic_cast<Coin*>(entityA);
	Coin* isBcoin = dynamic_cast<Coin*>(entityB);
    Mushroom* isAmushroom = dynamic_cast<Mushroom*>(entityA);
    Mushroom* isBmushroom = dynamic_cast<Mushroom*>(entityB);
    Item* isAitem = dynamic_cast<Item*>(entityA);
    Item* isBitem = dynamic_cast<Item*>(entityB);
    if (isAmario && isBtile|| isBmario&& isAtile)
    {
        CollisionInfo AtoB = isAmario ? isAmario->CheckCollisionType(*isBtile) : isBmario->CheckCollisionType(*isAtile);
        if (isAmario)
            HandleMarioWithTile(isAmario, isBtile, AtoB);
        else
            HandleMarioWithTile(isBmario, isAtile, AtoB);
    }
    else if (isAfireball && isBtile || isBfireball && isAtile)
    {
        CollisionInfo AtoB = isAfireball ? isAfireball->CheckCollisionType(*isBtile) : isBfireball->CheckCollisionType(*isAtile);
        if (isAfireball)
            HandleFireballWithTile(isAfireball, isBtile, AtoB);
        else
            HandleFireballWithTile(isBfireball, isAtile, AtoB);
    }
    else if(isAmario && isBcoin || isBmario && isAcoin)
    {
        Mario* mario = isAmario ? isAmario : isBmario;
        Coin* coin = isAcoin ? isAcoin : isBcoin;
        CollisionInfo AtoB = mario->CheckCollisionType(*coin);
        HandleMarioWithCoin(mario, coin, AtoB);
	}
    else if (isAmario && isBmushroom || isBmario && isAmushroom)
    {
        Mario* mario = isAmario ? isAmario : isBmario;
        Mushroom* mushroom = isAmushroom ? isAmushroom : isBmushroom;
        CollisionInfo AtoB = mario->CheckCollisionType(*mushroom);
        HandleMarioWithMushroom(mario, mushroom, AtoB);
    }
    else if (isAitem && isBtile || isBitem && isAtile)
    {
        Item* item = isAitem ? isAitem : isBitem;
        Tile* tile = isAtile ? isAtile : isBtile;
        CollisionInfo AtoB = item->CheckCollisionType(*tile);
        HandleItemWithTile(item, tile, AtoB);
    }
}

void CollisionMediator::HandleMarioWithMushroom(Mario*& mario, Mushroom*& mushroom, CollisionInfo AtoB)
{
    if (AtoB == COLLISION_NONE)
        return;
    if (mushroom->getState() != ItemState::IDLE)
        return;

    if (CheckCollisionRecs(mario->getRect(), mushroom->getRect())) {
        mushroom->collect();
        mario->changeToBig();
    }
}

void CollisionMediator::HandleItemWithTile(Item*& item, Tile*& tile, CollisionInfo AtoB)
{
    if (AtoB == COLLISION_NONE)
        return;

    Vector2 velocity = item->getVelocity();
    Vector2 position = item->getPosition();

    switch (AtoB)
    {
    case COLLISION_SOUTH:
        position.y = tile->getPosition().y - item->getSize().y;
        velocity.y = 0;
        break;
    case COLLISION_NORTH:
        position.y = tile->getPosition().y + tile->getSize().y;
        velocity.y = 0;
        break;
    case COLLISION_EAST:
    case COLLISION_WEST:
        velocity.x = -velocity.x; // Reverse direction
        break;
    default:
        break;
    }
    item->setPosition(position);
    item->setVelocity(velocity);
}