#include "raylib.h"
#include "Entity.h"
#include "ExclamationBlock.h"

ExclamationBlock::ExclamationBlock(Vector2 pos, Vector2 size, Color color) :
    ExclamationBlock(pos, size, color, 0, 1) {}

ExclamationBlock::ExclamationBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame) :
    Block(pos, size, color, frameTime, maxFrame, 0) {
        sprite = &ResourceManager::getInstance().getTexture("Exclamation_Block");
    }

ExclamationBlock::~ExclamationBlock() = default;   

void ExclamationBlock::updateStateAndPhysic() {}

void ExclamationBlock::updateSprite() {}

void ExclamationBlock::Draw() {
    if (!sprite) {
        printf("ExclamationBlock sprite is null!\n");
        return;
    }
    DrawTexture(*sprite, pos.x, pos.y, WHITE);
}