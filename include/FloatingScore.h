#pragma once
#include "GameClock.h"
#include "ResourceManager.h"
#include "DrawalbeObj.h"

class FloatingScore {
public:
    FloatingScore();

    void Update();
    void Draw();
	void loadSprite(const std::string& spritePath);
    void setPosition(Vector2 pos);

private:
    Vector2 position;
    Texture2D* spriteTexture;
    float timer;
    float duration;
};