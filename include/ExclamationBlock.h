#pragma once
#include "raylib.h"
#include "Entity.h"
#include "Block.h"

class ExclamationBlock : public Block {
    public:
        ExclamationBlock(Vector2 pos, Vector2 size, Color color);
        ExclamationBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame);
        ~ExclamationBlock() override;
    
        void updateStateAndPhysic() override;
        void updateSprite() override;
        void Draw() override;  
};