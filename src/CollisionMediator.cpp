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

void CollisionMediator::HandleMarioWithCoin(Mario*& mario, Coin*& coin)
{
    if (coin->getState() != ItemState::IDLE)
        return;

    if (CheckCollisionRecs(mario->getRect(), coin->getRect())) {
        coin->collect();
        // Optionally: mario->addScore(), play sound, etc.
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
        HandleMarioWithCoin(mario, coin);
	}
}