#include "ItemFactory.h"


Item *ItemFactory::createItem(const std::string &type, Vector2 pos, Direction direction)
{
    if (type == "Coin") {
        return new Coin(pos, {32,32}, WHITE, 0.04f, 4, IDLE);
    }
    else if (type == "Mushroom") {
        return new Mushroom(pos, {32,32}, WHITE, 0.1f, 4, DIRECTION_LEFT);
    }
    else if (type == "UpMushroom") {
        return new UpMushroom(pos, {32,32}, WHITE, 0.1f, 4, DIRECTION_LEFT);
    }
    else if (type == "FireFlower") {
        return new FireFlower(pos, {32,32}, WHITE, 0.1f, 2);
    }
    else if (type == "Star") {
        return new Star(pos, {32,32}, WHITE, 0.1f, 2, DIRECTION_RIGHT);
    }
    else if (type == "UpMoon") {
        return new UpMoon(pos, {32,32}, WHITE, 0.1f, 2, DIRECTION_RIGHT);
    }
    else if (type == "ClearToken") {
		return new ClearToken(pos, { 64,32 }, WHITE, 0.1f, 2);
    }
    return nullptr;
}
