#include "raylib.h"
#include "CloudBlock.h"

CloudBlock::CloudBlock(Vector2 pos, Vector2 size, Color color) :
    CloudBlock(pos, size, color, 0, 1) {}

CloudBlock::CloudBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame) :
    Block(pos, size, color, frameTime, maxFrame, 0) {
        sprite = &ResourceManager::getInstance().getTexture("Cloud_Block");
    }

CloudBlock::~CloudBlock() = default;   

void CloudBlock::updateStateAndPhysic() {}

void CloudBlock::updateSprite() {}

void CloudBlock::Draw() {
    if (!sprite) {
        printf("CloudBlock sprite is null!\n");
        return;
    }
    DrawTexture(*sprite, pos.x, pos.y, WHITE);
}