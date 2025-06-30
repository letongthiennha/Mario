#include "Star.h"
#include "ResourceManager.h"
#include "World.h"

Star::Star(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame, Direction initialDirection) :
	Item(pos, size, color, frameTime, maxFrame), initialDirection(initialDirection) {
	sprite = &ResourceManager::getInstance().getTexture("STAR");
	floatingScore.loadSprite("1000_POINTS");
	float speed = 150.0f;
	if (initialDirection == DIRECTION_LEFT) {
		setVelocity(Vector2(-speed, 0));
		initialSpeedX = -speed;
	}
	else {
		setVelocity(Vector2(speed, 0));
		initialSpeedX = speed;
	}
	NorthHb.SetSize({ size.x / 2, 2 });
	SouthHb.SetSize({ size.x / 2 , 2 });
	WestHb.SetSize({ 2, size.y - 4 });
	EastHb.SetSize({ 2, size.y - 4 });
}

void Star::playSoundCollision() {
	SoundController::getInstance().PlaySound("POWER_UP");
}

void Star::updateSprite() {
	if (state == ItemState::IDLE) {
		sprite = &ResourceManager::getInstance().getTexture("STAR");
	}
	else if (state == ItemState::BEING_HIT) {
		floatingScore.Update();
		setVelocity({ 0, 0 });
		frameAcum += GameClock::getInstance().FIXED_TIME_STEP;
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

void Star::Draw() {
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

void Star::collect() {
	Item::collect();
	sprite = &ResourceManager::getInstance().getTexture("STAR_DUST_0");
}

void Star::updateStateAndPhysic() {
	Entity::updateStateAndPhysic();

	if (onGround && !isJumping) {
		isJumping = true;
		jumpTimer = 0.0f;
		velocity.y = -150.0f;
	}
	
	if(isJumping){
		jumpTimer += GameClock::getInstance().FIXED_TIME_STEP;
		if (jumpTimer >= jumpDuration) {
			isJumping = false;
		}
		else {
			velocity.y -= World::GetGravity() * GameClock::getInstance().FIXED_TIME_STEP;
		}
	}

	if (!onGround && !isJumping) {
		velocity.y += World::GetGravity() * GameClock::getInstance().FIXED_TIME_STEP;
	}
}


