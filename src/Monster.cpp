/* File: Monster.cpp */
#include "../include/Monster.h"

Monster::Monster(Vector2 pos, Vector2 size, Color color, float speed) 
    : Entity(pos, size, color), speed(speed), isActive(true) {}

Monster::~Monster() {}

void Monster::updateStateAndPhysic() {
    if (!isActive) return;
    pos.x += velocity.x * GameClock::GetUpdateDeltaTime();
    pos.y += velocity.y * GameClock::GetUpdateDeltaTime();
    velocity.y += World::GetGravity() * GameClock::GetUpdateDeltaTime();
    updateHitboxes();
}

void Monster::Draw() {
    if (!isActive) return;
    if (sprite != nullptr) {
        DrawTexture(*sprite, pos.x, pos.y, WHITE);
    }
}

bool Monster::getIsActive() const {
    return isActive;
}

void Monster::setIsActive(bool active) {
    isActive = active;
}