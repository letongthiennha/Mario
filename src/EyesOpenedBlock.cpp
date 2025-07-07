#include "raylib.h"
#include "Entity.h"
#include "EyesOpenedBlock.h"

EyesOpenedBlock::EyesOpenedBlock(Vector2 pos, Vector2 size, Color color) :
    EyesOpenedBlock(pos, size, color, 0.1f, 3)  {
        hit = false;
    }

EyesOpenedBlock::EyesOpenedBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame) :
    Block(pos, size, color, frameTime, maxFrame, 0) {
        hit = false;
        currFrame = 0;
        frameAcum = 0;
        sprite = &ResourceManager::getInstance().getTexture("Eyes_Opened_Block_0");
    }

EyesOpenedBlock::~EyesOpenedBlock() = default;   

void EyesOpenedBlock::updateStateAndPhysic() {
    Entity::updateStateAndPhysic();
    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame++;
        if (currFrame > maxFrame) currFrame = 0;
        frameAcum -= frameTime;
    }
}

void EyesOpenedBlock::updateSprite() {
    std::string key = "Eyes_Opened_Block_" + std::to_string(currFrame);
    sprite = &ResourceManager::getInstance().getTexture(key);
}

void EyesOpenedBlock::Draw() {
    updateSprite();
    if (!sprite) {
        printf("EyesOpenedBlock sprite is null!\n");
        return;
    }
    DrawTexture(*sprite, pos.x, pos.y, WHITE);
}
