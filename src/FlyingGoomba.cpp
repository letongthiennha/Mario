#include "../include/FlyingGoomba.h"
#include "../include/ResourceManager.h"
#include "../include/GameClock.h"
#include "../include/World.h"
#include "../include/Tile.h"

FlyingGoomba::FlyingGoomba(Vector2 pos, float speed)
    : Monster(pos, Vector2{66, 50}, WHITE, speed),
      hoverRange(30), hoverSpeed(100), originalY(pos.y), hoverDirection(1)
{
    velocity.x = speed;
    sprite = &ResourceManager::getTexture("FLYING_GOOMBA_0_RIGHT");
}

void FlyingGoomba::updateSprite() {
    if (!isActive) return;

    std::string dir = (velocity.x >= 0) ? "R" : "L";
    std::string key = "flyingGoomba" + std::to_string(currFrame) + dir;

    sprite = &ResourceManager::getTexture(key);
}


void FlyingGoomba::updateStateAndPhysic() {
    if (!isActive) return;

    float delta = GameClock::GetUpdateDeltaTime();

    // ─ Hovering behavior ─
    pos.y += hoverDirection * hoverSpeed * delta;
    if (pos.y > originalY + hoverRange) {
        pos.y = originalY + hoverRange;
        hoverDirection = -1;
    } else if (pos.y < originalY - hoverRange) {
        pos.y = originalY - hoverRange;
        hoverDirection = 1;
    }

    // ─ Direction logic ─
    if (GetRandomValue(0, 1000) < 2) {
        velocity.x = (GetRandomValue(0, 1) == 0) ? -std::abs(speed) : std::abs(speed);
    } else {
        velocity.x = (velocity.x >= 0) ? std::abs(speed) : -std::abs(speed);
    }

    velocity.y = 0.0f; // override gravity
    Monster::updateStateAndPhysic(); // apply movement, update rects & hitboxes

    // ─ Animation ─
    frameAcum += delta;
    frameTime = 0.15f;
    maxFrame = 3;
    if (frameAcum >= frameTime) {
        currFrame = (currFrame + 1) % (maxFrame + 1);
        frameAcum = 0.0f;
    }

    updateSprite();
}

void FlyingGoomba::handleCollision(const Tile& tile, CollisionInfo type) {
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

void FlyingGoomba::Draw() {
    if (!isActive) return;
    updateSprite();
    if (sprite == nullptr || sprite->id == 0) return;

    Rectangle source = {0, 0, (float)sprite->width, (float)sprite->height};
    Rectangle dest = {pos.x, pos.y, size.x, size.y};
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(*sprite, source, dest, origin, 0.0f, WHITE);
}
