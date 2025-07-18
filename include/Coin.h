#pragma once
#include "Item.h"
#include "ResourceManager.h"
#include "SoundController.h"

class Coin : public Item {
public:
    bool isItem = false;

    Coin(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame);
    Coin(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame, ItemState s);

    void playSoundCollision() override;
    void updateSprite() override;
    void Draw() override;
    void collect() override;
};