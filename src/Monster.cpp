#include "Monster.h"
#include "Level.h"
#include "GameClock.h"
#include "FloatingScore.h"
#include <iostream>

Monster::Monster(Vector2 pos, Vector2 size, Color color, float speed)
    : Entity(pos, size, color), speed(speed), isActive(true),
      blinkAcum(0.0f), blinkTime(0.15f), deathDuration(1.0f), frameTime(0.25f),
      isVisible(true), deathAcum(0.0f), floatingScore(nullptr), hitsToDie(1) {
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
        currFrame = 0;
        frameAcum = 0.0f;
        deathAcum = 0.0f;
        velocity = {0.0f, 0.0f};
        blinkAcum = 0.0f;
        isVisible = true;
        if (floatingScore != nullptr) {
            delete floatingScore;
        }
        floatingScore = new FloatingScore();
        floatingScore->setPosition({pos.x + size.x / 2, pos.y - 20});
        floatingScore->loadSprite("400_POINTS");
        updateSprite();
        std::cout << "[Monster] Die called, starting puff animation\n";
    }
}

void Monster::updateStateAndPhysic() {
    if (!isActive && state != ENTITY_STATE_DYING && state != ENTITY_STATE_SQUASHED) return;
    if (floatingScore != nullptr) {
        floatingScore->Update();
    }
    float delta = GameClock::getInstance().DeltaTime;

    if (state == ENTITY_STATE_DYING) {
        deathAcum += delta;
        frameAcum += delta;
        if (frameAcum >= frameTime) {
            currFrame = (currFrame + 1) % 4;
            frameAcum -= frameTime;
            std::cout << "[Monster] Dying frame: " << currFrame << ", frameAcum=" << frameAcum << "\n";
        }
        if (deathAcum >= deathDuration) {
            state = ENTITY_STATE_TO_BE_REMOVED;
            std::cout << "[Monster] Marked for removal\n";
        }
        updateSprite();
        if (sprite == nullptr || sprite->id == 0) {
            std::cout << "[Monster] Null sprite during dying, frame=" << currFrame << "\n";
        }
        return;
    }

    if (state == ENTITY_STATE_SQUASHED) {
        updateSprite();
        if (sprite == nullptr || sprite->id == 0) {
            std::cout << "[Monster] Null sprite during squashed, frame=" << currFrame << "\n";
        }
        return;
    }

    Entity::updateStateAndPhysic();
    velocity.y += Level::GRAVITY * delta;
    if (velocity.y > 0 && state != ENTITY_STATE_ON_GROUND) {
        state = ENTITY_STATE_FALLING;
    }
}

void Monster::Draw() {
    if (floatingScore != nullptr) {
        floatingScore->Draw();
    }
    if (sprite == nullptr || sprite->id == 0) {
        std::cout << "[Monster] Null sprite during Draw\n";
        return;
    }
    Rectangle source = {0, 0, (float)sprite->width, (float)sprite->height};
    Rectangle dest = {pos.x, pos.y, size.x, size.y};
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(*sprite, source, dest, origin, 0.0f, WHITE);
}

bool Monster::getIsActive() const {
    return isActive;
}

void Monster::setIsActive(bool active) {
    isActive = active;
}