#include "raylib.h"
#include "Entity.h"
#include "EyesClosedBlock.h"

EyesClosedBlock::EyesClosedBlock(Vector2 pos, Vector2 size, Color color) :
    EyesClosedBlock(pos, size, color, 0, 1) {}

EyesClosedBlock::EyesClosedBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame) :
    Block(pos, size, color, frameTime, maxFrame, 0) {
        sprite = &ResourceManager::getInstance().getTexture("Eyes_Closed_Block");
    }

EyesClosedBlock::~EyesClosedBlock() = default;   

void EyesClosedBlock::updateStateAndPhysic() {}

void EyesClosedBlock::updateSprite() {}

void EyesClosedBlock::Draw() {
    if (!sprite) {
        printf("EyesClosedBlock sprite is null!\n");
        return;
    }
    DrawTexture(*sprite, pos.x, pos.y, WHITE);
}