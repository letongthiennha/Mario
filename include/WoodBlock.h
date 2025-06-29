#pragma once
#include "raylib.h"
#include "Entity.h"
#include "Block.h"

class WoodBlock : public Block {
    public:
        WoodBlock(Vector2 pos, Vector2 size, Color color);
        WoodBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame);
        ~WoodBlock() override;

        void updateStateAndPhysic() override;
        void updateSprite() override;
        void Draw() override;
};