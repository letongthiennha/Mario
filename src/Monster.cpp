#include "../include/Monster.h"
#include "../include/World.h"
#include "../include/GameClock.h"
#include <iostream>

Monster::Monster(Vector2 pos, Vector2 size, Color color, float speed) 
    : Entity(pos, size, color), speed(speed), isActive(true), 
      blinkAcum(0.0f), blinkTime(0.15f), deathDuration(1.0f), isVisible(true), deathAcum(0.0f) {}

Monster::~Monster() {}

void Monster::die() {
    if (state != ENTITY_STATE_DYING) {
        state = ENTITY_STATE_DYING;
        velocity = {0.0f, 0.0f}; // Stop movement
        blinkAcum = 0.0f;
        deathAcum = 0.0f;
        isVisible = true;
        std::cout << "Monster die called at position (" << pos.x << ", " << pos.y << ")" << std::endl;
    }
}

void Monster::updateStateAndPhysic() {
    if (!isActive && state != ENTITY_STATE_DYING) return;

    float delta = GameClock::GetUpdateDeltaTime();

//Death animation________________________
    if (state == ENTITY_STATE_DYING) {
        deathAcum += delta;
        blinkAcum += delta;

        if (blinkAcum >= blinkTime) {
            isVisible = !isVisible;
            blinkAcum = 0.0f;
        }

        std::cout << "[DYING] deathAcum = " << deathAcum << ", blinkAcum = " << blinkAcum 
                  << ", isVisible = " << isVisible << std::endl;

        if (deathAcum >= deathDuration) {
            isActive = false;
            std::cout << "[DEATH COMPLETE] Monster is now inactive at (" 
                      << pos.x << ", " << pos.y << ")" << std::endl;
        }

        updateHitboxes();
        return;
    }
//End of death animation_____________________

    // Normal behavior
    pos.x += velocity.x * delta;
    pos.y += velocity.y * delta;
    velocity.y += World::GetGravity() * delta;
    if (velocity.y > 0 && state != ENTITY_STATE_ON_GROUND) {
        state = ENTITY_STATE_FALLING;
    }
    updateHitboxes();
}


void Monster::Draw() {
    if (!isActive || (state == ENTITY_STATE_DYING && !isVisible)) return;
    if (sprite != nullptr && sprite->id != 0) {
        Rectangle source = {0, 0, (float)sprite->width, (float)sprite->height};
        Rectangle dest = {pos.x, pos.y, size.x, size.y};
        Vector2 origin = {0.0f, 0.0f};
        DrawTexturePro(*sprite, source, dest, origin, 0.0f, WHITE);
    }
}

bool Monster::getIsActive() const {
    return isActive;
}

void Monster::setIsActive(bool active) {
    isActive = active;
}