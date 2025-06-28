#include "Item.h"

Item::Item(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame):
	Entity(pos, size, color, frameTime, maxFrame), state(IDLE), disappearTimer(0.3f){ }

void Item::collect() {
    if (state == ItemState::IDLE) {
        state = ItemState::BEING_HIT;
    }
}

void Item::setState(ItemState newState) {
    state = newState;
}


