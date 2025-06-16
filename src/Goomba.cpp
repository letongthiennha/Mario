#include "../include/Goomba.h"

void Goomba::updateSprite() {
    if (!isActive) return;
    if (velocity.x > 0) {
        sprite = &ResourceManager::getTexture("GOOMBA_0_RIGHT");
    } else {
        sprite = &ResourceManager::getTexture("GOOMBA_0_LEFT");
    }
}

Goomba::Goomba(Vector2 pos, float speed) 
    : Monster(pos, Vector2{32, 32}, BROWN, speed) {
    velocity.x = -speed; // Move left by default
    sprite = &ResourceManager::getTexture("GOOMBA_0_LEFT");
}

//Helper function to check if a tile is below the Goomba
bool Goomba::isTileBelowAhead(const std::vector<Tile*>& tiles) {
    Vector2 aheadPos = pos;
    aheadPos.x += (velocity.x > 0) ? size.x : -1; // Check ahead, just outside current box
    aheadPos.y += size.y + 1; // One pixel below bottom

    Rectangle checkRect = { aheadPos.x, aheadPos.y, 1, 1 };

    for (auto tile : tiles) {
        if (CheckCollisionRecs(checkRect, tile->getRect())) {
            return true; // Ground exists ahead
        }
    }
    return false; // Cliff ahead!
}


void Goomba::updateStateAndPhysic() {
    if (!isActive) return;
    // Smart AI: Cliff detection
    if (!isTileBelowAhead(World::getInstance()->getInteractiveTiles())) {
        velocity.x = -velocity.x; // Turn around to avoid falling
    }
    Monster::updateStateAndPhysic();// Call base class to update position and velocity
    if (pos.x < 0) {
        pos.x = 0;
        velocity.x = speed; // Reverse to move right
    }
    updateSprite();
}

void Goomba::handleCollision(const Tile& tile, CollisionInfo type) {
    if (type == COLLISION_NONE) return;
    switch (type) {
        case COLLISION_SOUTH:
            setPosition({pos.x, tile.getPosition().y - size.y});
            velocity.y = 0;
            state = ENTITY_STATE_ON_GROUD;
            break;
        case COLLISION_EAST:
            setPosition({tile.getPosition().x - size.x, pos.y});
            velocity.x = -speed; // Move left
            break;
        case COLLISION_WEST:
            setPosition({tile.getPosition().x + tile.getSize().x, pos.y});
            velocity.x = speed;  // Move right
            break;
        default:
            break;
    }
}

void Goomba::Draw() {
    if (!isActive) return;
    updateSprite();
    if (sprite == nullptr || sprite->id == 0) {
        // Optionally print debug info
        // std::cout << "Goomba sprite not loaded or invalid!" << std::endl;
        return;
    }
    // Use the actual size of the Goomba (size.x, size.y) for destination rectangle
    Rectangle source = {0, 0, (float)sprite->width, (float)sprite->height};
    Rectangle dest = {pos.x, pos.y, size.x, size.y};
    Vector2 origin = {0.0f, 0.0f}; // Draw from top-left corner
    DrawTexturePro(*sprite, source, dest, origin, 0.0f, WHITE);
}