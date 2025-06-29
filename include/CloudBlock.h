#pragma once
#include "raylib.h"
#include "Entity.h"
#include "Block.h"

class CloudBlock : public Block {
    public:
    CloudBlock(Vector2 pos, Vector2 size, Color color);
    CloudBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame);
    ~CloudBlock() override;

    void updateStateAndPhysic() override;
    void updateSprite() override;
    void Draw() override;
};