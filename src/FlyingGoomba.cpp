#include "FlyingGoomba.h"
#include "ResourceManager.h"
#include "GameClock.h"
#include "Level.h"
#include "Tile.h"

FlyingGoomba::FlyingGoomba(Vector2 pos, float speed)
    : Monster(pos, Vector2{66, 50}, WHITE, speed),
      hoverRange(30), hoverSpeed(100), originalY(pos.y), originalX(pos.x), hoverDirection(1) {
    velocity.x = speed;
    sprite = &ResourceManager::getInstance().getTexture("FLYING_GOOMBA_0_RIGHT");
    NorthHb.SetSize({size.x - 43, 1});
    SouthHb.SetSize({size.x - 43, 1});
    WestHb.SetSize({1, size.y });
    EastHb.SetSize({1, size.y });
}

void FlyingGoomba::updateSprite() {
    if (!isActive ) return;
    if(state==ENTITY_STATE_DYING){
    std::string key="PUFT_" + std::to_string(currFrame);
    sprite = &ResourceManager::getInstance().getTexture(key);
    return;
    }
    std::string dir = (velocity.x >= 0) ? "R" : "L";
    std::string key = "flyingGoomba" + std::to_string(currFrame) + dir;
    sprite = &ResourceManager::getInstance().getTexture(key);
}

void FlyingGoomba::updateStateAndPhysic() {

    if (!isActive || state == ENTITY_STATE_DYING) {
        Monster::updateStateAndPhysic();
        return;
    }
    float delta = GameClock::getInstance().DeltaTime;
    pos.y += hoverDirection * hoverSpeed * delta;
    if (pos.y > originalY + hoverRange) {
        pos.y = originalY + hoverRange;
        hoverDirection = -1;
    } else if (pos.y < originalY - hoverRange) {
        pos.y = originalY - hoverRange;
        hoverDirection = 1;
    }
    if (GetRandomValue(0, 1000) < 2) {
        velocity.x = (GetRandomValue(0, 1) == 0) ? -std::abs(speed) : std::abs(speed);
    } else {
        velocity.x = (velocity.x >= 0) ? std::abs(speed) : -std::abs(speed);
    }
    if(pos.x < originalX - 150 || pos.x > originalX + 150) {
        velocity.x = (pos.x < originalX) ? std::abs(speed) : -std::abs(speed);
    }
    
    velocity.y = 0.0f;
    Monster::updateStateAndPhysic();
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
    if (state == ENTITY_STATE_DYING) return;
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

