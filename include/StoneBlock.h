#pragma once
#include "raylib.h"
#include "Entity.h"
#include "Block.h"


class StoneBlock : public Block {
    public:
        StoneBlock( Vector2 pos, Vector2 size, Color color);
        StoneBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame);
        ~StoneBlock() override;

        void updateStateAndPhysic() override;
        void updateSprite() override;
        void Draw() override;
};