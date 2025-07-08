#include "CourseClearToken.h"

ClearToken::ClearToken(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame) :
	Item(pos, size, color, frameTime, maxFrame, ItemState::IDLE){
	sprite = &ResourceManager::getInstance().getTexture("COURSE_CLEAR_TOKEN");
	startingPosY = pos.y;
	endingPosY = pos.y - 7 * 32.0f;

	NorthHb.SetSize({ size.x / 2, 2 });
	SouthHb.SetSize({ size.x / 2, 2 });
	WestHb.SetSize({ 2, size.y - 4 });
	EastHb.SetSize({ 2, size.y - 4 });
}

ClearToken::ClearToken(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame, ItemState s):
	Item(pos, size, color, frameTime, maxFrame, s) {
	sprite = &ResourceManager::getInstance().getTexture("COURSE_CLEAR_TOKEN");

	startingPosY = pos.y;
	endingPosY = pos.y - 7 * 32.0f;

	NorthHb.SetSize({ size.x / 2, 2 });
	SouthHb.SetSize({ size.x / 2, 2 });
	WestHb.SetSize({ 2, size.y - 4 });
	EastHb.SetSize({ 2, size.y - 4 });
}

void ClearToken::playSoundCollision(){
//...
}

void ClearToken::updateSprite() {
	if(state == ItemState::IDLE) {
		sprite = &ResourceManager::getInstance().getTexture("COURSE_CLEAR_TOKEN");
	} 
	else if (state == ItemState::BEING_HIT) {
		frameAcum += GameClock::getInstance().DeltaTime;
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

void ClearToken::Draw() {
	updateSprite();
	if (state == ItemState::IDLE && sprite) {
		DrawTexturePro(*sprite, { 0, 0, (float)sprite->width, (float)sprite->height }, { pos.x, pos.y, size.x, size.y }, { 0, 0 }, 0.0f, color);
	}
	else if (state == ItemState::BEING_HIT && sprite) {
		DrawTexturePro(*sprite, { 0, 0, (float)sprite->width, (float)sprite->height }, { initialPos.x, initialPos.y, size.x, size.y }, { 0, 0 }, 0.0f, color);
	}
}

void ClearToken::collect(){
	Item::collect();
	sprite = &ResourceManager::getInstance().getTexture("STAR_DUST_0");
}

void ClearToken::updateStateAndPhysic() {
	if (state != ItemState::IDLE) return;

	float dt = GameClock::getInstance().DeltaTime;
	pos.y += direction * verticalVelocity * dt;

	if(pos.y>=startingPosY){
		pos.y = startingPosY;
		direction = -1;
	} else if (pos.y <= endingPosY) {
		pos.y = endingPosY;
		direction = 1;
	}

	//printf("ClearToken y: %f, direction: %d, velocity: %f, dt: %f\n", pos.y, direction, verticalVelocity, dt);
}