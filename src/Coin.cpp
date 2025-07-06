#include "Coin.h"
#include "GameClock.h"
#include <string>


Coin::Coin(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame): Item(pos, size, color, frameTime, maxFrame){
	sprite = &ResourceManager::getInstance().getTexture("COIN_0");
	floatingScore.loadSprite("200_POINTS");

    NorthHb.SetSize({ size.x / 2, 2 });
    SouthHb.SetSize({ size.x / 2, 2 });
    WestHb.SetSize({ 2, size.y - 4 });
    EastHb.SetSize({ 2, size.y - 4 });
}

Coin::Coin(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame, ItemState s):
    Item(pos, size, color, frameTime, maxFrame, s) {
        sprite = &ResourceManager::getInstance().getTexture("COIN_0");
        floatingScore.loadSprite("200_POINTS");

        NorthHb.SetSize({ size.x / 2, 2 });
        SouthHb.SetSize({ size.x / 2, 2 });
        WestHb.SetSize({ 2, size.y - 4 });
        EastHb.SetSize({ 2, size.y - 4 });
}

void Coin::updateSprite() {
    if (state == ItemState::IDLE) {
        frameAcum +=GameClock::getInstance().DeltaTime;
        if (frameAcum >= frameTime) {
            frameAcum -= frameTime;
            currFrame = (currFrame + 1) % maxFrame;
            sprite = &ResourceManager::getInstance().getTexture("COIN_" + std::to_string(currFrame));
        }
    }
    else if (state == ItemState::BEING_HIT) {
		floatingScore.Update();
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

void Coin::Draw() {
	updateSprite();
	if(state==ItemState::IDLE&& sprite) {
		DrawTexturePro(*sprite, { 0, 0, (float)sprite->width, (float)sprite->height }, { pos.x, pos.y, size.x, size.y }, { 0, 0 }, 0.0f, color);
	}
    else if (state == ItemState::BEING_HIT && sprite) {
		DrawTexturePro(*sprite, { 0, 0, (float)sprite->width, (float)sprite->height }, { initialPos.x, initialPos.y, size.x, size.y }, { 0, 0 }, 0.0f, color);
        floatingScore.Draw();
    }
}

void Coin::playSoundCollision(){
    SoundController::getInstance().PlaySound("COIN_COLLECTION");
}

void Coin::collect() {
    Item::collect();
	sprite = &ResourceManager::getInstance().getTexture("STAR_DUST_0");
}


