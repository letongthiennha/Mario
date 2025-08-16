#include "3UpMoon.h"
#include "ResourceManager.h"
#include "SoundController.h"
#include "GameClock.h"
#include "Level.h"

UpMoon::UpMoon(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame, Direction initialDirection) :
	Item(pos, size, color, frameTime, maxFrame), initialDirection(initialDirection) {
	sprite = &ResourceManager::getInstance().getTexture("UP_MOON");
	floatingScore.loadSprite("3_UP");
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
	SouthHb.SetSize({ size.x / 2 , 2 });
	WestHb.SetSize({ 2, size.y - 4 });
	EastHb.SetSize({ 2, size.y - 4 });
}

void UpMoon::playSoundCollision() {
	SoundController::getInstance().PlaySound("POWER_UP");
}

void UpMoon::updateSprite() {
	static const float DeltaTime = GetFrameTime();
	if (state == ItemState::IDLE) {
		sprite = &ResourceManager::getInstance().getTexture("UP_MOON");
	}
	else if (state == ItemState::BEING_HIT) {
		floatingScore.Update();
		setVelocity({ 0, 0 });
		frameAcum +=DeltaTime;
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

void UpMoon::Draw() {
	updateSprite();
	if (state == ItemState::COLLECTED)
		return;
	DrawTexturePro(*sprite, { 0, 0, (float)sprite->width, (float)sprite->height }, { pos.x, pos.y, size.x, size.y }, { 0, 0 }, 0.0f, color);
	if (state == ItemState::BEING_HIT) {
		floatingScore.Draw();
	}
	/*SouthHb.Draw();
	NorthHb.Draw();
	EastHb.Draw();
	WestHb.Draw();*/
}

void UpMoon::collect() {
	Item::collect();
	sprite = &ResourceManager::getInstance().getTexture("STAR_DUST_0");
}

void UpMoon::updateStateAndPhysic() {
	Entity::updateStateAndPhysic();
	if (!onGround) {
		velocity.y += Level::GRAVITY *GameClock::getInstance().DeltaTime;
	}
}