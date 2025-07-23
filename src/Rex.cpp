#include "Rex.h"
#include "GameClock.h"
#include "ResourceManager.h"
#include "Level.h"

Rex::Rex(Vector2 pos, float speed)
    : Monster(pos, Vector2{64, 64}, WHITE, speed, 2), hitCooldown(0.0f) { // 2 hits to die
    velocity.x = speed;
    frameTime = 0.15f;
    maxFrame = 1;
    currFrame = 0;
    frameAcum = 0.0f;
    updateHitboxes();
}
void Rex::die() {
    if (state == ENTITY_STATE_DYING || state == ENTITY_STATE_TO_BE_REMOVED || !isActive || hitCooldown > 0.0f) {
        return; // Prevent invalid state transitions or hits during cooldown
    }

    hitCooldown = 0.2f; // Set 0.2-second cooldown after a hit

    // Transition to dying state
    state = ENTITY_STATE_DYING;
    currFrame = 0;
    frameTime = 0.15f;
    velocity = {GetRandomValue(0, 1) == 0 ? 200.0f : -200.0f, -200.0f}; // Random horizontal velocity, upward jump
    blinkAcum = 0.0f;
    deathAcum = 0.0f;
    isVisible = true;
    if (floatingScore != nullptr) {
        delete floatingScore;
        floatingScore = nullptr;
    }
    floatingScore = new FloatingScore();
    floatingScore->setPosition({pos.x + size.x / 2, pos.y - 20});
    floatingScore->loadSprite("200_POINTS");
    hitsToDie = 0; // Ensure no further hits
}

void Rex::updateSprite() {
    if (state == ENTITY_STATE_DYING) {
        std::string key = "PUFT_" + std::to_string(currFrame);
        sprite = &ResourceManager::getInstance().getTexture(key);
    } else {
        std::string dir = (velocity.x >= 0) ? "RIGHT" : "LEFT";
        std::string key = "REX_" + std::to_string(hitsToDie) + "_" + std::to_string(currFrame) + "_" + dir;
        sprite = &ResourceManager::getInstance().getTexture(key);
    }
}

void Rex::updateStateAndPhysic() {
    if (!isActive) return;

    Monster::updateStateAndPhysic(); // Handles movement, gravity, and dying

    float delta = GameClock::getInstance().DeltaTime;

    // Update hit cooldown
    if (hitCooldown > 0.0f) {
        hitCooldown -= delta;
        if (hitCooldown < 0.0f) hitCooldown = 0.0f;
    }

    if (state != ENTITY_STATE_DYING) {
        frameAcum += delta;
        if (frameAcum >= frameTime) {
            currFrame = (currFrame + 1) % (maxFrame + 1);
            frameAcum = 0.0f;
        }
    }

    updateSprite();
}

void Rex::handleCollision(const Tile& tile, CollisionInfo type) {
    if (state == ENTITY_STATE_DYING) return;
    if (type == COLLISION_NONE) return;

    switch (type) {
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



