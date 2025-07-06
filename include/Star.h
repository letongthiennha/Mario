#pragma once
#include "Item.h"

class Star : public Item {
public:
	Star(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame, Direction initialDirection);

	void playSoundCollision() override;
	void updateSprite() override;
	void Draw() override;
	void collect() override;
	void update();
	void updateStateAndPhysic() override;
private:
	float initialSpeedX;
	Direction initialDirection;
	float jumpTimer = 0.0f;
	const float jumpDuration = 0.15f;
	bool isJumping = false;
};