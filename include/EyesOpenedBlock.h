#pragma once
#include "raylib.h"
#include "Entity.h"
#include "Block.h"

class EyesOpenedBlock : public Block {
    public:
    EyesOpenedBlock(Vector2 pos, Vector2 size, Color color);
    EyesOpenedBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame);
    ~EyesOpenedBlock() override;

    void updateStateAndPhysic() override;
    void updateSprite() override;
    void Draw() override;
};