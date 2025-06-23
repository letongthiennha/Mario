#include "../include/BlueKoopaTroopa.h"
#include "../include/ResourceManager.h"
#include "../include/GameClock.h"
#include "../include/World.h"

BlueKoopaTroopa::BlueKoopaTroopa(Vector2 pos, float speed)
    : Monster(pos, Vector2{32, 48}, BLUE, speed) {
    velocity.x = -speed; // Move left by default
    sprite = &ResourceManager::getTexture("BLUE_KOOPA_0_LEFT");
}

void BlueKoopaTroopa::updateSprite() {
    if (!isActive) return;
    std::string dir = (velocity.x >= 0) ? "RIGHT" : "LEFT";
    std::string key = "BLUE_KOOPA_" + std::to_string(currFrame) + "_" + dir;
    sprite = &ResourceManager::getTexture(key);
}

bool BlueKoopaTroopa::isTileBelowAhead(const std::vector<Tile*>& tiles) {
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

void BlueKoopaTroopa::updateStateAndPhysic() {
    if (!isActive) return;
    float delta = GameClock::GetUpdateDeltaTime();
    if (!isTileBelowAhead(World::getInstance()->getInteractiveTiles())) {
        velocity.x = -velocity.x;
    }
    pos.x += velocity.x * delta;
    pos.y += velocity.y * delta;
    velocity.y += World::GetGravity() * delta;
    if (velocity.y > 0 && state != ENTITY_STATE_ON_GROUD) {
        state = ENTITY_STATE_FALLING;
    }
    frameAcum += delta;
    frameTime = 0.2f;
    maxFrame = 1;
    if (frameAcum >= frameTime) {
        currFrame = (currFrame + 1) % (maxFrame + 1);
        frameAcum = 0.0f;
    }
    updateHitboxes();
    updateSprite();
}

void BlueKoopaTroopa::handleCollision(const Tile& tile, CollisionInfo type) {
    if (type == COLLISION_NONE) return;
    switch (type) {
        case COLLISION_SOUTH:
            setPosition({pos.x, tile.getPosition().y - size.y});
            velocity.y = 0;
            state = ENTITY_STATE_ON_GROUD;
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

void BlueKoopaTroopa::Draw() {
    if (!isActive) return;
    updateSprite();
    if (sprite == nullptr || sprite->id == 0) return;
    Rectangle source = {0, 0, (float)sprite->width, (float)sprite->height};
    Rectangle dest = {pos.x, pos.y, size.x, size.y};
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(*sprite, source, dest, origin, 0.0f, WHITE);
}