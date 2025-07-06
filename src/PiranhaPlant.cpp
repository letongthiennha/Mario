#include "PiranhaPlant.h"
#include "ResourceManager.h"
#include "GameClock.h"

PiranhaPlant::PiranhaPlant(Vector2 pos, float speed)
    : Monster(pos, Vector2{32, 48}, RED, speed),
      minY(pos.y - 48), maxY(pos.y), animVel(80.0f),
      waitAcum(0.0f), waitTime(2.0f), waiting(false) {
    velocity = {0.0f, 0.0f};
    sprite = &ResourceManager::getInstance().getTexture("PIRANHA_0");
}

void PiranhaPlant::updateSprite() {
    if (!isActive || state == ENTITY_STATE_DYING) return;
    std::string key = "PIRANHA_" + std::to_string(currFrame);
    sprite = &ResourceManager::getInstance().getTexture(key);
}

void PiranhaPlant::updateStateAndPhysic() {
    if (!isActive || state == ENTITY_STATE_DYING) {
        Monster::updateStateAndPhysic();
        return;
    }
    float delta = GameClock::getInstance().DeltaTime;
    if (!waiting) {
        pos.y += animVel * delta;
        if (pos.y < minY) {
            pos.y = minY;
            animVel = -animVel;
            waiting = true;
        } else if (pos.y > maxY) {
            pos.y = maxY;
            animVel = -animVel;
            waiting = true;
        }
    } else {
        waitAcum += delta;
        if (waitAcum >= waitTime) {
            waitAcum = 0.0f;
            waiting = false;
        }
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

void PiranhaPlant::handleCollision(const Tile& tile, CollisionInfo type) {
    // Stationary, no tile collision response
}

void PiranhaPlant::Draw() {
    if (!isActive || (state == ENTITY_STATE_DYING && !isVisible)) return;
    updateSprite();
    if (sprite == nullptr || sprite->id == 0) return;
    Rectangle source = {0, 0, (float)sprite->width, (float)sprite->height};
    Rectangle dest = {pos.x, pos.y, size.x, size.y};
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(*sprite, source, dest, origin, 0.0f, WHITE);
}