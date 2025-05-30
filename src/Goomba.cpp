/* File: Goomba.cpp */
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
    : Monster(pos, Vector2{30, 20}, BROWN, speed) {
    velocity.x = -speed; // Move left by default, using passed speed
    sprite = &ResourceManager::getTexture("GOOMBA_0_LEFT");
}

void Goomba::updateStateAndPhysic() {
    if (!isActive) return;
    Monster::updateStateAndPhysic();
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
            velocity.x = -speed; // Reverse direction
            break;
        case COLLISION_WEST:
            setPosition({tile.getPosition().x + tile.getSize().x, pos.y});
            velocity.x = speed; // Reverse direction
            break;
        default:
            break;
    }
}

void Goomba::Draw() {
    if (!isActive) return;
    updateSprite();
    if (sprite != nullptr) {
        Rectangle source = {0, 0, (float)sprite->width, (float)sprite->height};
        Rectangle dest = {pos.x, pos.y, 30.0f, 20.0f};
        Vector2 origin = {15.0f, 10.0f};
        DrawTexturePro(*sprite, source, dest, origin, 0.0f, WHITE);
    }
}