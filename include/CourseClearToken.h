#pragma once
#include "Item.h"
#include "ResourceManager.h"
#include "SoundControoler.h"

class ClearToken : public Item {
private:
	float startingPosY;
    float endingPosY;
    float verticalVelocity = 100.0f;
    int direction = 1;
public:
    ClearToken(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame);
    ClearToken(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame, ItemState s);

    void playSoundCollision() override;
    void updateSprite() override;
    void Draw() override;
    void collect() override;
    void updateStateAndPhysic() override;
};