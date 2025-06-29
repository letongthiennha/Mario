#include "FireFlower.h"
#include "GameClock.h"
#include "ResourceManager.h"
#include "SoundControoler.h"
#include "World.h"
#include <string>


FireFlower::FireFlower(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame) : Item(pos, size, color, frameTime, maxFrame) {
    sprite = &ResourceManager::getInstance().getTexture("FIRE_FLOWER_0");

    NorthHb.SetSize({ size.x / 2, 2 });
    SouthHb.SetSize({ size.x / 2, 2 });
    WestHb.SetSize({ 2, size.y - 4 });
    EastHb.SetSize({ 2, size.y - 4 });
}

void FireFlower::updateSprite() {
    if (state == ItemState::IDLE) {
        frameAcum += GameClock::getInstance().FIXED_TIME_STEP;
        if (frameAcum >= frameTime) {
            frameAcum -= frameTime;
            currFrame = (currFrame + 1) % maxFrame;
            sprite = &ResourceManager::getInstance().getTexture("FIRE_FLOWER_" + std::to_string(currFrame));
        }
    }
    else if (state == ItemState::BEING_HIT) {
        frameAcum += GameClock::getInstance().FIXED_TIME_STEP;
        if (frameAcum >= disappearTimer) {
            frameAcum -= disappearTimer;
            currFrame++;
            if (currFrame < maxFrame) {
                sprite = &ResourceManager::getInstance().getTexture("STAR_DUST_" + std::to_string(currFrame));
            }
            else {
                state = ItemState::COLLECTED;
            }
        }
    }
}

void FireFlower::Draw() {
    updateSprite();
    if (state == ItemState::IDLE && sprite) {
        DrawTexturePro(*sprite, { 0, 0, (float)sprite->width, (float)sprite->height }, { pos.x, pos.y, size.x, size.y }, { 0, 0 }, 0.0f, color);
    }
    else if (state == ItemState::BEING_HIT && sprite) {
        DrawTexturePro(*sprite, { 0, 0, (float)sprite->width, (float)sprite->height }, { initialPos.x, initialPos.y, size.x, size.y }, { 0, 0 }, 0.0f, color);
    }
}

void FireFlower::playSoundCollision() {
    SoundController::getInstance().PlaySound("POWER_UP");
}

void FireFlower::collect() {
    Item::collect();
    sprite = &ResourceManager::getInstance().getTexture("STAR_DUST_0");
    maxFrame = 4;
}

void FireFlower::updateStateAndPhysic() {
    Entity::updateStateAndPhysic();
    if (!onGround) {
        velocity.y += World::GetGravity() * GameClock::getInstance().FIXED_TIME_STEP;
    }
}


