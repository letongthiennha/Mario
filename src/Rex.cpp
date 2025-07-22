#include "Rex.h"
#include "GameClock.h"
#include "ResourceManager.h"
#include "Level.h"
#include <iostream>

Rex::Rex(Vector2 pos, float speed)
    : Monster(pos, Vector2{64, 64}, WHITE, speed) {
    velocity.x = speed;
    hitsToDie = 2;
    frameTime = 0.15f;
    maxFrame = 1;
    currFrame = 0;
    frameAcum = 0.0f;
    hitCooldown = 0.0f;
    squashDuration = 0.0f;
    sprite = &ResourceManager::getInstance().getTexture("REX_2_0_RIGHT");
}

void Rex::updateSprite() {
    std::string key;
    if (state == ENTITY_STATE_DYING) {
        key = "PUFT_" + std::to_string(currFrame);
    } else {
        std::string dir = (velocity.x >= 0) ? "RIGHT" : "LEFT";
        key = "REX_" + std::to_string(hitsToDie) + "_" + std::to_string(currFrame) + "_" + dir;
    }
    try {
        sprite = &ResourceManager::getInstance().getTexture(key);
        if (sprite == nullptr || sprite->id == 0) {
            std::cout << "[Rex] Failed to load sprite: " << key << "\n";
            sprite = &ResourceManager::getInstance().getTexture("REX_2_0_RIGHT");
        }
    } catch (const std::exception& e) {
        std::cout << "[Rex] Exception loading sprite: " << key << ", error: " << e.what() << "\n";
        sprite = &ResourceManager::getInstance().getTexture("REX_2_0_RIGHT");
    }
}

void Rex::updateStateAndPhysic() {
    if (!isActive) return;

    float delta = GameClock::getInstance().DeltaTime;

    if (hitCooldown > 0) {
        hitCooldown -= delta;
    }

    if (state == ENTITY_STATE_DYING) {
        Monster::updateStateAndPhysic();
        return;
    }

    if (state == ENTITY_STATE_SQUASHED) {
        squashDuration += delta;
        if (squashDuration >= 0.5f) {
            state = ENTITY_STATE_DYING;
            currFrame = 0;
            frameAcum = 0.0f;
            deathAcum = 0.0f;
            updateSprite();
            std::cout << "[Rex] Transition to dying at pos.y=" << posOnDying.y << "\n";
        }
        return;
    }

    Monster::updateStateAndPhysic();

    if (state == ENTITY_STATE_ON_GROUND && velocity.x != 0) {
        frameAcum += delta;
        if (frameAcum >= frameTime) {
            currFrame = (currFrame + 1) % (maxFrame + 1);
            frameAcum = 0.0f;
        }
    }

    updateSprite();
}

void Rex::handleCollision(const Tile& tile, CollisionInfo type) {
    if (state == ENTITY_STATE_DYING || state == ENTITY_STATE_SQUASHED) return;
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

void Rex::onHit() {
    if (state == ENTITY_STATE_DYING || state == ENTITY_STATE_TO_BE_REMOVED || state == ENTITY_STATE_SQUASHED) return;
    if (hitCooldown > 0) {
        std::cout << "[Rex] Hit ignored due to cooldown: " << hitCooldown << "\n";
        return;
    }

    posOnDying = pos;
    std::cout << "[Rex] onHit called, hitsToDie=" << hitsToDie << "\n";
    if (hitsToDie == 1) {
        hitsToDie = 0;
        state = ENTITY_STATE_SQUASHED;
        squashDuration = 0.0f;
        velocity = {0.0f, 0.0f};
        updateSprite();
        std::cout << "[Rex] Entered squashed state at pos.y=" << posOnDying.y << "\n";
    } else {
        hitsToDie--;
        float feetY = pos.y + size.y;
        setSize(Vector2{64, 32});
        pos.y = feetY - size.y;
        hitCooldown = 0.2f;
        std::cout << "[Rex] Squashed at pos.y=" << pos.y << ", feetY=" << feetY << "\n";
    }
}

void Rex::Draw() {
    if (sprite == nullptr || sprite->id == 0) {
        std::cout << "[Rex] Null sprite at pos.y=" << pos.y << ", state=" << state << "\n";
        return;
    }

    Rectangle source = {0, 0, (float)sprite->width, (float)sprite->height};
    Rectangle dest = (state == ENTITY_STATE_DYING || state == ENTITY_STATE_SQUASHED) ?
        Rectangle{posOnDying.x, posOnDying.y, size.x, size.y} :
        Rectangle{pos.x, pos.y, size.x, size.y};
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(*sprite, source, dest, origin, 0.0f, WHITE);

    if (floatingScore != nullptr) {
        floatingScore->Draw();
    }
    if (state == ENTITY_STATE_DYING) {
        std::cout << "[Rex] Drawing dying frame: " << currFrame << ", pos.y=" << posOnDying.y << "\n";
    } else if (state == ENTITY_STATE_SQUASHED) {
        std::cout << "[Rex] Drawing squashed frame: " << currFrame << ", pos.y=" << posOnDying.y << "\n";
    }
}