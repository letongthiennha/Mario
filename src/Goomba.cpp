#include "Goomba.h"
#include "ResourceManager.h"
#include "GameClock.h"
#include "Level.h"
#include <iostream>

Goomba::Goomba(Vector2 pos, float speed) 
    : Monster(pos, Vector2{32, 32}, BROWN, speed) {
    velocity.x = speed; // Move left by default
    sprite = &ResourceManager::getInstance().getTexture("GOOMBA_0_RIGHT");
    frameTime = 0.15f; // Adjusted for walking animation
    maxFrame = 1; // 2 frames: 0 and 1
    currFrame = 0;
    frameAcum = 0.0f;
    NorthHb.SetSize({size.x - 16, 1});
    SouthHb.SetSize({size.x - 16, 1});
    WestHb.SetSize({1, size.y - 16});
    EastHb.SetSize({1, size.y - 16});
    updateHitboxes();
}

void Goomba::updateSprite() {
    if (!isActive && state == ENTITY_STATE_DYING) return;
    std::string dir = (velocity.x >= 0) ? "RIGHT" : "LEFT";
    std::string key = "GOOMBA_" + std::to_string(currFrame) + "_" + dir;
    sprite = &ResourceManager::getInstance().getTexture(key);
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
    float delta = GameClock::getInstance().DeltaTime;
    
    Monster::updateStateAndPhysic();
    // Prevent sliding off the Level
    if (pos.x < 0) {
        pos.x = 0;
        velocity.x = speed;
    }
    if (state == ENTITY_STATE_ON_GROUND && velocity.x != 0) {
        frameAcum += delta;
        if (frameAcum >= frameTime) {
            currFrame = (currFrame + 1) % (maxFrame + 1);
            frameAcum -=frameTime;
        }
    }
}



void Goomba::Draw() {
    if (floatingScore != nullptr) {
        floatingScore->Draw();
    }
    if (!isActive || (state == ENTITY_STATE_DYING && !isVisible))
     return;
    updateSprite();
    if (sprite == nullptr || sprite->id == 0) {
        return;
    }
    Rectangle source = {0, 0, (float)sprite->width, (float)sprite->height};
    Rectangle dest = {pos.x, pos.y, size.x, size.y};
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(*sprite, source, dest, origin, 0.0f, WHITE);

}