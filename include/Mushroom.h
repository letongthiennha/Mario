#pragma once
#include "Item.h"

class Mushroom : public Item {
public:
	Mushroom(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame, Direction initialDirection);

	void playSoundCollision() override;
	void updateSprite() override;
	void Draw() override;
	void collect() override;
	void update();
	void updateStateAndPhysic() override;
private:
	Direction initialDirection;
};