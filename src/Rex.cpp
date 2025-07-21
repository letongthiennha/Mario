#include "Rex.h"
#include "GameClock.h"
#include "ResourceManager.h"
#include "Level.h"

Rex::Rex(Vector2 pos, float speed)
    : Monster(pos, Vector2{64, 64}, WHITE, speed) {
    velocity.x = speed;
    frameTime = 0.15f;
    maxFrame = 1;
    currFrame = 0;
    frameAcum = 0.0f;
    updateHitboxes();
}

void Rex::updateSprite() {
    if (state == ENTITY_STATE_DYING) {
        std::string key = "PUFT_" + std::to_string(currentDyingFrame);
        sprite = &ResourceManager::getInstance().getTexture(key);
    } else {
        std::string dir = (velocity.x >= 0) ? "RIGHT" : "LEFT";
        std::string key = "REX_" + std::to_string(hitsToDie) + "_" + std::to_string(currFrame) + "_" + dir;
        sprite = &ResourceManager::getInstance().getTexture(key);
    }
}

void Rex::updateStateAndPhysic() {
    if (!isActive) return;

    Monster::updateStateAndPhysic(); // handles movement, gravity, and dying

    float delta = GameClock::getInstance().DeltaTime;

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



