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

    sprite = &ResourceManager::getInstance().getTexture("BANZAIBILL_0");

    updateHitboxes();
}


void BanzaiBill::updateStateAndPhysic() {
    if (!isActive) return;
                if(floatingScore != nullptr) {
        floatingScore->Update();

    }
    if(state==ENTITY_STATE_DYING){
        velocity.x = -150.0f;
        velocity.y = 300.0f; // This makes BanzaiBill fly down


    }

    Entity::updateStateAndPhysic();

    // Remove when off the left edge of the screen
    if (pos.x + size.x < 0||pos.y>=1000.0f) {
        state = ENTITY_STATE_TO_BE_REMOVED;  // Mark for removal or hide
    }

    updateHitboxes();
}

void BanzaiBill::updateSprite() {
    if (!isActive ) return;
    sprite = &ResourceManager::getInstance().getTexture("BANZAIBILL_0");
}





void BanzaiBill::handleCollision(const Tile& tile, CollisionInfo type) {
    // BanzaiBill is unstoppable — no collision response needed
}
