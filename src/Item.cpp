#include "Item.h"
#include "GameClock.h"
#include "World.h"

Item::Item(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame):
	Entity(pos, size, color, frameTime, maxFrame), state(IDLE), disappearTimer(0.05f), initialPos(pos){ }

void Item::collect() {
    if (state == ItemState::IDLE) {
        state = ItemState::BEING_HIT;
        currFrame = 0;
        frameAcum = 0;
        playSoundCollision();
    }
}

void Item::setState(ItemState newState) {
    state = newState;
}

void Item::startPopUp(float distance, float speed) {
    poppingUp = true;
    popUpDistance = 0.0f;
    popUpMaxDistance = distance;
    popUpSpeed = speed;
}

void Item::popUp() {
    if (poppingUp) {
        float move = popUpSpeed * GameClock::getInstance().FIXED_TIME_STEP;
        pos.y -= move;
        popUpDistance += move;
        if (popUpDistance >= popUpMaxDistance) {
            pos.y = initialPos.y - popUpMaxDistance;
            poppingUp = false;
            // Optionally: set state to collected or idle, or trigger sound/effect
        }
    }
    // Call base class or add other item logic here
    Entity::updateStateAndPhysic();
}

void Item::playSoundPopUp(){ }

void Item::setOnGround(bool onGround) {
	this->onGround = onGround;
}

ItemState Item::getState() const{
    return state;
}


