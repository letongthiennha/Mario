#include "Monster.h"
#include "Level.h"
#include "GameClock.h"
#include "FloatingScore.h"
#include <iostream>

Monster::Monster(Vector2 pos, Vector2 size, Color color, float speed) 
    : Entity(pos, size, color), speed(speed), isActive(true), 
      blinkAcum(0.0f), blinkTime(0.15f), deathDuration(1.0f), isVisible(true), deathAcum(0.0f),floatingScore(nullptr) {

      }

Monster::~Monster() {
    if (floatingScore != nullptr) {
        delete floatingScore;
        floatingScore = nullptr;
    }

}

void Monster::die() {
    if (state != ENTITY_STATE_DYING) {
        state = ENTITY_STATE_DYING;
        velocity = {0.0f, 0.0f}; // Stop movement
        blinkAcum = 0.0f;
        deathAcum = 0.0f;
        isVisible = true;
        floatingScore = new FloatingScore();
        floatingScore->setPosition({pos.x + size.x / 2, pos.y - 20});
        floatingScore->loadSprite("400_POINTS"); // Load the score sprite
    }


}

void Monster::updateStateAndPhysic() {
    if (!isActive && state != ENTITY_STATE_DYING) return;
    if(floatingScore != nullptr) {
        floatingScore->Update();

    }
    float delta = GameClock::getInstance().DeltaTime;

//Death animation________________________
    if (state == ENTITY_STATE_DYING) {
        deathAcum += delta;
        blinkAcum += delta;

        if (blinkAcum >= blinkTime) {
            isVisible = !isVisible;
            blinkAcum = 0.0f;
        }

        if (deathAcum >= deathDuration) {
            state = ENTITY_STATE_TO_BE_REMOVED; // Change state to be removed after death duration

        }

        updateHitboxes();
        return;
    }
//End of death animation_____________________

    // Normal behavior
    Entity::updateStateAndPhysic();
    velocity.y += Level::GRAVITY * delta;
    if (velocity.y > 0&& state != ENTITY_STATE_ON_GROUND) {
        state = ENTITY_STATE_FALLING;
    }
    updateHitboxes();
}


void Monster::Draw() {
    if (floatingScore != nullptr) {
        floatingScore->Draw();
    }
    if (!isActive || (state == ENTITY_STATE_DYING && !isVisible)) 
    return;
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