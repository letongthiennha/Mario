#pragma once
#include "Entity.h"
#include "ItemState.h"

class Item : public Entity {
public:
    Item(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame);

    virtual void updateSprite() override = 0;
    virtual void Draw() override = 0;

    virtual void collect();
	virtual void playSoundCollision() = 0;
    virtual void playSoundPopUp();

    void setState(ItemState newState);
    void startPopUp(float distance, float speed);
    virtual void popUp();
    void setOnGround(bool onGround);
	ItemState getState() const;

protected:
    ItemState state;
    float disappearTimer = 0.0f;
    bool poppingUp = false;
    float popUpDistance = 0.0f;
    float popUpMaxDistance = 40.0f;
    float popUpSpeed = 120.0f;
    bool onGround = true;
    Vector2 initialPos;
};