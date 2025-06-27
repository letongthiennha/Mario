#include "Item.h"

Item::Item(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame):
	Entity(pos, size, color, frameTime, maxFrame), collected(false){ }

void Item::collect() {
	collected = true;
}

