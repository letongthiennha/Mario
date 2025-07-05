#include "../include/Goomba.h"
#include "../include/ResourceManager.h"
#include "../include/GameClock.h"
#include "../include/World.h"
#include <iostream>

Goomba::Goomba(Vector2 pos, float speed) 
    : Monster(pos, Vector2{32, 32}, BROWN, speed) {
    velocity.x = -speed; // Move left by default
    sprite = &ResourceManager::getTexture("GOOMBA_0_LEFT");
    frameTime = 0.15f; // Adjusted for walking animation
    maxFrame = 1; // 2 frames: 0 and 1
    currFrame = 0;
    frameAcum = 0.0f;
}

void Goomba::updateSprite() {
    if (!isActive && state == ENTITY_STATE_DYING) return;
    std::string dir = (velocity.x >= 0) ? "RIGHT" : "LEFT";
    std::string key = "GOOMBA_" + std::to_string(currFrame) + "_" + dir;
    sprite = &ResourceManager::getTexture(key);
}

bool Goomba::isTileBelowAhead(const std::vector<Tile*>& tiles) {
    if (state == ENTITY_STATE_DYING) return false;
    Vector2 aheadPos = pos;
    aheadPos.x += (velocity.x > 0) ? size.x : -1;
    aheadPos.y += size.y + 1;
    Rectangle checkRect = { aheadPos.x, aheadPos.y, 1, 1 };
    for (auto tile : tiles) {
        if (CheckCollisionRecs(checkRect, tile->getRect())) {
            return true;
        }
    }
    return false;
}

void Goomba::updateStateAndPhysic() {
    if (!isActive && state == ENTITY_STATE_DYING) {
        Monster::updateStateAndPhysic(); // Use base class for death animation
        return;
    }
    float delta = GameClock::GetUpdateDeltaTime();
    // Reverse direction if no tile ahead
    if (!isTileBelowAhead(World::getInstance()->getInteractiveTiles())) {
        velocity.x = -velocity.x;
    }
    Monster::updateStateAndPhysic();
    // Prevent sliding off the world
    if (pos.x < 0) {
        pos.x = 0;
        velocity.x = speed;
    }
    // Update animation only when on ground and moving
    if (state == ENTITY_STATE_ON_GROUND && velocity.x != 0) {
        frameAcum += delta;
        if (frameAcum >= frameTime) {
            currFrame = (currFrame + 1) % (maxFrame + 1);
            frameAcum = 0.0f;
            std::cout << "Goomba frame updated to " << currFrame << " at position (" 
                      << pos.x << ", " << pos.y << ")" << std::endl;
        }
    }
    updateSprite();
}

void Goomba::handleCollision(const Tile& tile, CollisionInfo type) {
    if (state == ENTITY_STATE_DYING) return;
    if (type == COLLISION_NONE) return;
    switch (type) {
        case COLLISION_SOUTH:
            setPosition({pos.x, tile.getPosition().y - size.y});
            velocity.y = 0;
            state = ENTITY_STATE_ON_GROUND;
            break;
        case COLLISION_EAST:
            setPosition({tile.getPosition().x - size.x, pos.y});
            velocity.x = -speed;
            break;
        case COLLISION_WEST:
            setPosition({tile.getPosition().x + tile.getSize().x, pos.y});
            velocity.x = speed;
            break;
        default:
            break;
    }
}

void Goomba::Draw() {
    if (!isActive && (state == ENTITY_STATE_DYING && !isVisible)) return;
    updateSprite();
    if (sprite == nullptr || sprite->id == 0) {
        std::cout << "Warning: Goomba sprite is null at position (" << pos.x << ", " << pos.y << ")" << std::endl;
        return;
    }
    Rectangle source = {0, 0, (float)sprite->width, (float)sprite->height};
    Rectangle dest = {pos.x, pos.y, size.x, size.y};
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(*sprite, source, dest, origin, 0.0f, WHITE);
}