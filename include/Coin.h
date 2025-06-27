#pragma once
#include "Item.h"
#include "ResourceManager.h"

class Coin : public Item {
public:
    Coin(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame);

    void updateSprite() override;
    void Draw() override;
};