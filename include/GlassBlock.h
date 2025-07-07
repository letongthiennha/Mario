#pragma once
#include "raylib.h"
#include "Entity.h"
#include "Block.h"

class GlassBlock : public Block {
    public:
        GlassBlock(Vector2 pos, Vector2 size, Color color);
        GlassBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame);
        ~GlassBlock() override;
    
        void updateStateAndPhysic() override;
        void updateSprite() override;
        void Draw() override;        
};