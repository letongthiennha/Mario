#include "ItemFactory.h"

Item* ItemFactory::createItem(
    const std::string& type,
    Vector2 pos,
    Vector2 size,
    Color color,
    float frameTime,
    int maxFrame,
    int extra,
    Direction direction
) {
    if (type == "Coin") {
        return new Coin(pos, size, color, frameTime, maxFrame, static_cast<ItemState>(extra));
    }
    else if (type == "Mushroom") {
        return new Mushroom(pos, size, color, frameTime, maxFrame, direction);
    }
    else if (type == "UpMushroom") {
        return new UpMushroom(pos, size, color, frameTime, maxFrame, direction);
    }
    else if (type == "FireFlower") {
        return new FireFlower(pos, size, color, frameTime, maxFrame);
    }
    else if (type == "Star") {
        return new Star(pos, size, color, frameTime, maxFrame, direction);
    }
    else if (type == "UpMoon") {
        return new UpMoon(pos, size, color, frameTime, maxFrame, direction);
    }
    return nullptr;
}