#pragma once
#include "raylib.h"
#include "Entity.h"
#include "Block.h"

class EyesClosedBlock : public Block {
    public:
    EyesClosedBlock(Vector2 pos, Vector2 size, Color color);
    EyesClosedBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame);
    ~EyesClosedBlock() override;

    void updateStateAndPhysic() override;
    void updateSprite() override;
    void Draw() override;
};