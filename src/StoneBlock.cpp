#include "raylib.h"
#include "StoneBlock.h"

StoneBlock::StoneBlock(Vector2 pos, Vector2 size, Color color) :
    StoneBlock(pos, size, color, 0, 1) {}

StoneBlock::StoneBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame) :
    Block(pos, size, color, frameTime, maxFrame, 0) {
        sprite = &ResourceManager::getInstance().getTexture("Stone_Block");
    }

StoneBlock::~StoneBlock() = default;

void StoneBlock::updateStateAndPhysic() {}

void StoneBlock::updateSprite(){}

void StoneBlock::Draw() {
    if (!sprite) {
        printf("StoneBlock sprite is null!\n");
        return;
    }
    DrawTexture(*sprite, pos.x, pos.y, WHITE);
}