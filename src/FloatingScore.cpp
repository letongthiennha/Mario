#include "FloatingScore.h"


FloatingScore::FloatingScore() : position({ 0, 0 }), timer(0.0f), duration(0.1f), spriteTexture(nullptr) {
}

void FloatingScore::Update() {
	float deltaTime = GameClock::getInstance().FIXED_TIME_STEP;
	timer += deltaTime;
	if (timer < duration) position.y -= 30.f * deltaTime;
}

void FloatingScore::Draw(){
	if (spriteTexture == nullptr) return;
	DrawTexturePro(*spriteTexture, 
	{ 0, 0, (float)spriteTexture->width, (float)spriteTexture->height },
	{ position.x - (float)spriteTexture->width / 2.0f, position.y - (float)spriteTexture->height / 2.0f, (float)spriteTexture->width, (float)spriteTexture->height },
		{ 0.0f, 0.0f }, 0.0f, WHITE);
}

void FloatingScore::loadSprite(const std::string& spritePath) {
	spriteTexture = &ResourceManager::getInstance().getTexture(spritePath);
}

void FloatingScore::setPosition(Vector2 pos) {
	position = pos;
}
