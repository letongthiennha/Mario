#include "KoopaTroopa.h"
#include "ResourceManager.h"
#include "GameClock.h"
#include "Level.h"
#include "utils.h"

KoopaTroopa::KoopaTroopa(Vector2 pos, float speed)
    : Monster(pos, Vector2{32, 48}, BLUE, speed) {
    velocity.x =- speed;

    int randomColor =GetRandomValue(1,4); // Randomly choose blue or green
    switch (randomColor)  // Assuming 1 is blue, 2 is green, and 3 is red)
    {
    case 1: // Blue Koopa
        color = BLUE;
        sprite = &ResourceManager::getInstance().getTexture("BLUE_KOOPA_0_LEFT");
        break;
    case 2: // Green Koopa
        color = GREEN;
        sprite = &ResourceManager::getInstance().getTexture("GREEN_KOOPA_0_LEFT");
        break;
    case 3: // Red Koopa
        color = RED;
        sprite = &ResourceManager::getInstance().getTexture("RED_KOOPA_0_LEFT");
        break;
        /* code */
    case 4: // Yellow Koopa
        color = YELLOW;
        sprite = &ResourceManager::getInstance().getTexture("YELLOW_KOOPA_0_LEFT");
        break;
    }
    NorthHb.SetSize({size.x - 30, 1});
    SouthHb.SetSize({size.x-30, 1});
    WestHb.SetSize({1, size.y - 20});
    EastHb.SetSize({1, size.y - 20});
    updateHitboxes();
}

void KoopaTroopa::updateSprite() {
    if (!isActive || state == ENTITY_STATE_DYING) return;
    std::string dir = (velocity.x >= 0) ? "RIGHT" : "LEFT";
    std::string key;
    if( color == BLUE) {
        key = "BLUE_" ;
    } else if (color == GREEN) {
        key = "GREEN_" ;
    } else if (color == RED) {
        key = "RED_" ;
    }
    else if (color == YELLOW) {
        key = "YELLOW_" ;
    }
     key += "KOOPA_" + std::to_string(currFrame) + "_" + dir;
    sprite = &ResourceManager::getInstance().getTexture(key);
}

bool KoopaTroopa::isTileBelowAhead(const std::vector<Tile*>& tiles) {
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

void KoopaTroopa::updateStateAndPhysic() {
    if (!isActive || state == ENTITY_STATE_DYING) {
        Monster::updateStateAndPhysic();
        return;
    }
    float delta = GameClock::getInstance().DeltaTime;

    pos.x += velocity.x * delta;
    pos.y += velocity.y * delta;
    velocity.y += Level::GRAVITY * delta;
    if (velocity.y > 0 && state != ENTITY_STATE_ON_GROUND) {
        state = ENTITY_STATE_FALLING;
    }
    frameAcum += delta;
    frameTime = 0.2f;
    maxFrame = 1;
    if (frameAcum >= frameTime) {
        currFrame = (currFrame + 1) % (maxFrame + 1);
        frameAcum = 0.0f;
    }
    updateHitboxes();
    updateSprite();
}

void KoopaTroopa::handleCollision(const Tile& tile, CollisionInfo type) {
    if (state == ENTITY_STATE_DYING) return;
    if (type == COLLISION_NONE) return;
    switch (type) {
        case COLLISION_SOUTH:
            setPosition({pos.x, tile.getPosition().y - size.y});
            velocity.y = 0;
            state = ENTITY_STATE_ON_GROUND;
            break;
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

void KoopaTroopa::Draw() {
    if (floatingScore != nullptr) {
        floatingScore->Draw();
    }
    if (!isActive || (state == ENTITY_STATE_DYING && !isVisible)) return;
    updateSprite();
    if (sprite == nullptr || sprite->id == 0) return;
    Rectangle source = {0, 0, (float)sprite->width, (float)sprite->height};
    Rectangle dest = {pos.x, pos.y, size.x, size.y};
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(*sprite, source, dest, origin, 0.0f, WHITE);
    NorthHb.Draw();
    SouthHb.Draw();
    WestHb.Draw();
    EastHb.Draw();
}