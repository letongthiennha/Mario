#pragma once
#include "Entity.h"
#include "ItemState.h"

class Item : public Entity {
public:
    Item(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame);

    virtual void updateSprite() override = 0;
    virtual void Draw() override = 0;

    virtual void collect();

    void setState(ItemState newState);

protected:
    ItemState state;
    float disappearTimer = 0.0f;
};