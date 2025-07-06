#include "raylib.h"
#include "Entity.h"
#include "GlassBlock.h"

GlassBlock::GlassBlock(Vector2 pos, Vector2 size, Color color) :
    GlassBlock(pos, size, color, 0, 1) {}

GlassBlock::GlassBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame) :
    Block(pos, size, color, frameTime, maxFrame, 0) {
        sprite = &ResourceManager::getInstance().getTexture("Glass_Block");
    }

GlassBlock::~GlassBlock() = default;   

void GlassBlock::updateStateAndPhysic() {}

void GlassBlock::updateSprite() {}

void GlassBlock::Draw() {
    if (!sprite) {
        printf("GlassBlock sprite is null!\n");
        return;
    }
    DrawTexture(*sprite, pos.x, pos.y, WHITE);
}