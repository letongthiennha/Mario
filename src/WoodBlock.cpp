#include "raylib.h"
#include "WoodBlock.h"

WoodBlock::WoodBlock(Vector2 pos, Vector2 size, Color color) :
    WoodBlock(pos, size, color, 0, 1) {}

WoodBlock::WoodBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame) :
    Block(pos, size, color, frameTime, maxFrame, 0) {
    sprite = &ResourceManager::getInstance().getTexture("Wood_Block");
}

WoodBlock::~WoodBlock() = default;

void WoodBlock::updateStateAndPhysic() {}

void WoodBlock::updateSprite() {}

void WoodBlock::Draw() {
    if (!sprite) {
        printf("WoodBlock sprite is null!\n");
        return;
    }
    DrawTexture(*sprite, pos.x, pos.y, WHITE);
}