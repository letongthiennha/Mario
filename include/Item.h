#pragma once
#include "Entity.h"
#include "FloatingScore.h"
#include "ItemState.h"

class Item : public Entity {
public:
    Item(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame);
    Item(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame, ItemState s);

    virtual void updateSprite() override = 0;
    virtual void Draw() override = 0;

    virtual void collect();
	virtual void playSoundCollision() = 0;
    void playSoundPopUp();
    void Activate();

    void setState(ItemState newState);
    void setOnGround(bool onGround);
	ItemState getState() const;
    bool isOnGround() const;

protected:
    ItemState state;
    float disappearTimer = 0.0f;
    bool poppingUp = false;
    const float popUpDistance = 32.0f;
    const float popUpSpeed = 0.5f;
    float popUpOffset = 0.0f;
    bool onGround = true;
    Vector2 initialPos;
	FloatingScore floatingScore;
    bool FloatingScoreActive = false;
};