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

void CollisionMediator::HandleCollision(Entity *entityA, Entity *entityB)

{

    Mario* isAmario = dynamic_cast<Mario*>(entityA);
    Mario* isBmario = dynamic_cast<Mario*>(entityB);
    Fireball* isAfireball = dynamic_cast<Fireball*>(entityA);
    Fireball* isBfireball = dynamic_cast<Fireball*>(entityB);
    Tile* isAtile = dynamic_cast<Tile*>(entityA);
    Tile* isBtile = dynamic_cast<Tile*>(entityB);
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
    else if(isAmario && isBitem || isBmario && isAitem)
    {
        Mario* mario = isAmario ? isAmario : isBmario;
        Item* item = isAitem ? isAitem : isBitem;
        CollisionInfo AtoB = mario->CheckCollisionType(*item);
        HandleMarioWithItem(mario, item, AtoB);
	}
    else if (isAitem && isBtile || isBitem && isAtile)
    {
        Item* item = isAitem ? isAitem : isBitem;
        Tile* tile = isAtile ? isAtile : isBtile;
        CollisionInfo AtoB = item->CheckCollisionType(*tile);
        HandleItemWithTile(item, tile, AtoB);
    }
}

void CollisionMediator::HandleMarioWithItem(Mario*& mario, Item*& item, CollisionInfo AtoB) {
    if (AtoB == COLLISION_NONE)
        return;
    if (item->getState() != ItemState::IDLE)
        return;

    if (CheckCollisionRecs(mario->getRect(), item->getRect())) {
        if (auto* coin = dynamic_cast<Coin*>(item)) {
            coin->collect();
        }
        else if (auto* upMushroom = dynamic_cast<UpMushroom*>(item)) {
            upMushroom->collect();
            // Increase Mario's life by 1
        }
        else if (auto* mushroom = dynamic_cast<Mushroom*>(item)) {
            mushroom->collect();
            mario->changeToBig();
        }
        else if(auto* fireFlower= dynamic_cast<FireFlower*>(item)) {
            fireFlower->collect();
            mario->changeToFire();
        }
        // .... other items
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