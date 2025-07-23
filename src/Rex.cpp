#include "Rex.h"
#include "GameClock.h"
#include "ResourceManager.h"
#include "Level.h"
#include <iostream>

Rex::Rex(Vector2 pos, float speed)
    : Monster(pos, Vector2{40, 64}, WHITE, speed), isSquashed(false) {
    velocity.x = speed;
    frameTime = 0.15f;
    maxFrame = 1;
    currFrame = 0;
    frameAcum = 0.0f;
    sprite = &ResourceManager::getInstance().getTexture("REX_1_0_LEFT");
        NorthHb.SetSize({size.x - 30, 1});
    SouthHb.SetSize({size.x-30, 1});
    WestHb.SetSize({1, size.y - 20});
    EastHb.SetSize({1, size.y - 20});
}

void Rex::updateSprite() {
    std::string key;
    if (state == ENTITY_STATE_DYING) {
        key = "PUFT_" + std::to_string(currFrame);
    } else {
        std::string dir = (velocity.x >= 0) ? "RIGHT" : "LEFT";
        key = "REX_" + std::to_string((int)isSquashed) + "_" + std::to_string(currFrame) + "_" + dir;
    }
    sprite = &ResourceManager::getInstance().getTexture(key);
}

void Rex::updateStateAndPhysic() {
 if (!isActive && state == ENTITY_STATE_DYING) {
        Monster::updateStateAndPhysic(); // Use base class for death animation
        return;
    }
    float delta = GameClock::getInstance().DeltaTime;
    
    Monster::updateStateAndPhysic();
    // Prevent sliding off the Level
    if (pos.x < 0) {
        pos.x = 0;
        velocity.x = abs(velocity.x); // Reverse direction
    }
    if (state == ENTITY_STATE_ON_GROUND && velocity.x != 0) {
        frameAcum += delta;
        if (frameAcum >= frameTime) {
            currFrame = (currFrame + 1) % (maxFrame + 1);
            frameAcum -=frameTime;
        }
    }
}

void Rex::handleCollision(const Tile& tile, CollisionInfo type) {

}

void Rex::onHit() {
    if(!isSquashed){
        isSquashed = true;
        velocity.x = velocity.x/abs(velocity.x)*400.0f; // Stop movement on hit
        frameTime = 0.1f; // Faster animation for dying
        currFrame = 0;
        setSize(Vector2{32,32}); // Reset size
        
    NorthHb.SetSize({size.x - 30, 1});
    SouthHb.SetSize({size.x-30, 1});
    WestHb.SetSize({1, size.y - 20});
    EastHb.SetSize({1, size.y - 20});
        updateHitboxes();
    }
    else
        die();
}

