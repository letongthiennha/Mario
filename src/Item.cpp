#include "Item.h"
#include "GameClock.h"
#include "Level.h"
#include "SoundController.h"

Item::Item(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame):
	Entity(pos, size, color, frameTime, maxFrame), state(IDLE), disappearTimer(0.75f), initialPos(pos){ }

Item::Item(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame, ItemState s):
    Entity(pos, size, color, frameTime, maxFrame), state(s), disappearTimer(0.75f), initialPos(pos) {
}

void Item::collect() {
    if (state == ItemState::IDLE) {
        state = ItemState::BEING_HIT;
        currFrame = 0;
        frameAcum = 0;
        maxFrame = 0.02f;
        playSoundCollision();
        floatingScore.setPosition(pos);
    }
}

void Item::Activate() {
    if (state == POP_UP) {
        float move = std::min(popUpSpeed, popUpDistance - popUpOffset);
        pos.y -= move;
        popUpOffset += move;
        if (popUpOffset >= popUpDistance) {
            state = IDLE; // Or another state
            playSoundPopUp();
        }
        updateHitboxes();
    }
}

void Item::setState(ItemState newState) {
    state = newState;
}

void Item::playSoundPopUp(){ 
	SoundController::getInstance().PlaySound("POWER_UP_APPEARS");
}

void Item::setOnGround(bool onGround) {
	this->onGround = onGround;
}

ItemState Item::getState() const{
    return state;
}

bool Item::isOnGround() const {
	return onGround;
}


