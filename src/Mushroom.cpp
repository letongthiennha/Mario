#include "Mushroom.h"
#include "ResourceManager.h"
#include "Level.h"

Mushroom::Mushroom(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame, Direction initialDirection) :
	Item(pos, size, color, frameTime, maxFrame), initialDirection(initialDirection){
	sprite = &ResourceManager::getInstance().getTexture("MUSHROOM");
	floatingScore.loadSprite("1000_POINTS");
	float speed = 150.0f;
	if (initialDirection == DIRECTION_LEFT) {
		setVelocity(Vector2{-speed, 0});
		initialSpeedX = -speed;
	}
	else {
		setVelocity(Vector2{speed, 0});
		initialSpeedX = speed;
	}
	NorthHb.SetSize({ size.x / 2, 2 });
	SouthHb.SetSize({ size.x/2 , 2 });
	WestHb.SetSize({ 2, size.y - 4 });
	EastHb.SetSize({ 2, size.y - 4 });
}

void Mushroom::playSoundCollision() {
	SoundController::getInstance().PlaySound("POWER_UP");
}

void Mushroom::updateSprite() {
	if (state == ItemState::IDLE) {
		sprite = &ResourceManager::getInstance().getTexture("MUSHROOM");
	}
	else if (state == ItemState::BEING_HIT) {
		floatingScore.Update();
		setVelocity({ 0, 0 });
		frameAcum +=GameClock::getInstance().DeltaTime;
		if (frameAcum >= disappearTimer) {
			frameAcum -= disappearTimer;
			currFrame++;
			if (currFrame < maxFrame) {
				sprite = &ResourceManager::getInstance().getTexture("STAR_DUST_" + std::to_string(currFrame));
			}
			else {
				state = ItemState::COLLECTED;
			}
		}
	}
}

void Mushroom::Draw() {
	updateSprite();
	if(state==ItemState::COLLECTED)
		return;
	DrawTexturePro(*sprite, { 0, 0, (float)sprite->width, (float)sprite->height }, { pos.x, pos.y, size.x, size.y }, { 0, 0 }, 0.0f, color);
	if(state==ItemState::BEING_HIT) {
		floatingScore.Draw();
	}
	// SouthHb.Draw();
	// NorthHb.Draw();
	// EastHb.Draw();
	// WestHb.Draw();
}

void Mushroom::collect() {
	Item::collect();
	sprite = &ResourceManager::getInstance().getTexture("STAR_DUST_0");
}

void Mushroom::updateStateAndPhysic() {
	Entity::updateStateAndPhysic();
	if (!onGround) {
		velocity.y += Level::GRAVITY *GameClock::getInstance().DeltaTime;
	}
}

void Mushroom::setDirection(Direction direction) {
	initialDirection = direction;
}

