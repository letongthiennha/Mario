#pragma once
#include "Item.h"

class FireFlower : public Item {
public:
	FireFlower(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame);

	void playSoundCollision() override;
	void updateSprite() override;
	void Draw() override;
	void collect() override;
	void update();
	void updateStateAndPhysic() override;
};