#include "BanzaiBill.h"
#include "ResourceManager.h"
#include "GameClock.h"
#include "Level.h"
#include <iostream>

BanzaiBill::BanzaiBill(Vector2 pos, float speed)
    : Monster(pos, Vector2{96, 48}, WHITE, speed) {

    std::cout << "[BanzaiBill] Spawned at Y = " << pos.y << std::endl;

    velocity.x = -speed;
    velocity.y = 0.0f;

    sprite = &ResourceManager::getInstance().getTexture("BANZABILL_0");

    updateHitboxes();
}


void BanzaiBill::updateStateAndPhysic() {
    if (!isActive) return;

    float delta = GameClock::getInstance().DeltaTime;

    pos.x += velocity.x * delta;
    pos.y += velocity.y * delta;

    // Remove when off the left edge of the screen
    if (pos.x + size.x < 0) {
        setIsActive(false);  // Mark for removal or hide
    }

    updateHitboxes();
}

void BanzaiBill::updateSprite() {
    if (!isActive || state == ENTITY_STATE_DYING) return;

    sprite = &ResourceManager::getInstance().getTexture("BANZABILL_0");
}

void BanzaiBill::Draw() {
    if (!isActive || sprite == nullptr || sprite->id == 0) return;

    Rectangle source = { 0.0f, 0.0f, (float)-sprite->width, (float)sprite->height };
    Rectangle dest = { pos.x, pos.y, size.x, size.y };
    Vector2 origin = { 0.0f, 0.0f };

    DrawTexturePro(*sprite, source, dest, origin, 0.0f, WHITE);
}



void BanzaiBill::handleCollision(const Tile& tile, CollisionInfo type) {
    // BanzaiBill is unstoppable — no collision response needed
}
