#pragma once
#include "raylib.h"
#include "Entity.h"
#include "Block.h"

class WoodBlock : public Block {
    private:
        // No additional private members needed for now
        WoodBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame);

    public:
        WoodBlock(Vector2 pos, Vector2 size, Color color);
        ~WoodBlock() override;

        void updateStateAndPhysic() override;
        void updateSprite() override;
        void Draw() override;
};